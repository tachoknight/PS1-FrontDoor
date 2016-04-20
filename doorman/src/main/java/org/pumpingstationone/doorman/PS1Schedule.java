package org.pumpingstationone.doorman;

import biweekly.Biweekly;
import biweekly.ICalendar;
import biweekly.component.VEvent;
import biweekly.property.RecurrenceRule;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.net.MalformedURLException;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.time.Instant;
import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.time.ZonedDateTime;
import java.time.temporal.ChronoUnit;
import java.util.*;

public class PS1Schedule extends javax.servlet.http.HttpServlet {

    private List<UpcomingEvent> upcomingEvents = new ArrayList<>();

    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
        doGet(request, response);
    }

    protected void doGet(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
        setUpcomingEvents();

        ObjectMapper mapper = new ObjectMapper();
        String jsonInString = mapper.writeValueAsString(upcomingEvents);

        response.setContentType("application/json");
        PrintWriter out = response.getWriter();
        out.print(jsonInString);
        out.flush();
    }

    private String formatDateTime(Date date) {
        SimpleDateFormat ft = new SimpleDateFormat ("E MM/dd 'at' hh:mm:ss a zzz");

        return ft.format(date);
    }

    private void setUpcomingEvents() {
        try {

            upcomingEvents.clear();

            InputStream stream = new URL("https://calendar.google.com/calendar/ical/hhlp4gcgvdmifq5lcbk7e27om4%40group.calendar.google.com/public/basic.ics").openStream();
            List<ICalendar> icals = Biweekly.parse(stream).all();

            Instant today = ZonedDateTime.now().toInstant();
            System.out.println("Right now is from Date:\n" + today);
            LocalDateTime rightNow = LocalDateTime.ofInstant(today, ZoneOffset.systemDefault());

			Instant nextWeekInstant = today.plus(604800, ChronoUnit.SECONDS);

            for (VEvent event : icals.get(0).getEvents()) {

                Instant startInstant = Instant.ofEpochMilli(event.getDateStart().getValue().getTime());
                LocalDateTime startDate = LocalDateTime.ofInstant(startInstant, ZoneOffset.systemDefault());

                Instant endInstant = Instant.ofEpochMilli(event.getDateEnd().getValue().getTime());
                LocalDateTime endDate = LocalDateTime.ofInstant(endInstant, ZoneOffset.systemDefault());

                UpcomingEvent ue = new UpcomingEvent();

                // Does this event have any recurrence rules?
                RecurrenceRule rrule = event.getRecurrenceRule();

                if (rrule != null) {

                    //
                    // This event *does* have recurrence rules, which may
                    // be for a specific time period, or it may be open-ended
                    // going on forever.
                    //

                    Iterator<Date> it = rrule.getDateIterator(event.getDateStart().getValue());

                    while (it.hasNext()) {
                        Date ruleDate = it.next();
                        if (ruleDate.after(new Date()) && ruleDate.before(addDaysToDate(new Date(), 7))) {

                            // Ah, we have a recurring event taking place this week!
                            ue.setDescription(event.getSummary().getValue());
                            ue.setStartDate(formatDateTime(ruleDate));
                            ue.setStartEpoch(ruleDate.getTime());
                            ue.setEndEpoch(0);
                            upcomingEvents.add(ue);

                            System.err.println("rule date: " + ue.getDescription() + " - " + ue.getStartDate());
                            break;
                        } else {
                            // This is a guard against recurring events with no end date causing the
                            // program to go on forever; if the date in question is greater than two
                            // weeks from now, break out of the loop
                            if (ruleDate.after(addDaysToDate(new Date(), 14))) {
                                break;
                            }
                        }
                    }
                } else {
                    if (startInstant.isAfter(today) && startInstant.isBefore(nextWeekInstant)) {
                        ue.setDescription(event.getSummary().getValue());
                        ue.setStartDate(formatDateTime(event.getDateStart().getValue()));
                        ue.setEndDate(event.getDateEnd().getValue().toString());
                        ue.setStartEpoch(event.getDateStart().getValue().getTime());
                        ue.setEndEpoch(event.getDateEnd().getValue().getTime());
                        upcomingEvents.add(ue);

                        System.out.println("ONE SHOT EVENT: " + ue.getStartDate() + " to " + ue.getEndDate() + " - " + ue.getDescription());
                    }
                }
            }
            
            stream.close();
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

 	private Date addDaysToDate(final Date date, int noOfDays) {
        Date newDate = new Date(date.getTime());

        GregorianCalendar calendar = new GregorianCalendar();
        calendar.setTime(newDate);
        calendar.add(Calendar.DATE, noOfDays);
        newDate.setTime(calendar.getTime().getTime());

        return newDate;
    }
}
