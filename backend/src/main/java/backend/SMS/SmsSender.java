package backend.SMS;

import com.twilio.Twilio;
import com.twilio.rest.api.v2010.account.Message;
import com.twilio.type.PhoneNumber;

public class SmsSender {
    // Find your Account Sid and Auth Token at twilio.com/console
    public static final String ACCOUNT_SID =
            "AC849834d46b24a87088bfe68972936b40";
    public static final String AUTH_TOKEN =
            "3b4213ebce510f23a40ff405e4fd2524";



    public static void main(String... args) {
        Twilio.init(ACCOUNT_SID, AUTH_TOKEN);

        Message message = Message
                .creator(new PhoneNumber("+33651271989"), // to
                        new PhoneNumber("+33644647719"), // from
                        "Opening your suitcase")
                .create();

        System.out.println(message.getSid());
    }
}