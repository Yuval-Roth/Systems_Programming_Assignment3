package bgu.spl.net.impl.stomp.Service;

import java.io.IOException;

import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.genericServers.interfaces.ConnectionHandler;
import bgu.spl.net.impl.stomp.Service.STOMP_Frames.ErrorFrame;
import bgu.spl.net.impl.stomp.Service.STOMP_Frames.ExecutableFrame;

public class StompMessagingProtocolImpl implements MessagingProtocol<String> {

    @Override
    public String process(ConnectionHandler<String> handler,String message) {
        ExecutableFrame frame = null;
        try {
            frame = ExecutableFrame.parse(message);
        } catch (RuntimeException e) {
            e.printStackTrace();
            return ErrorFrame.get(e.getMessage(),message,true).toString();
        }

        if(frame == null){
            return ErrorFrame.get("The frame received does not contain a valid STOMP command"
                                                    ,message,true).toString();
        }
        else{
            return frame.execute(handler);
        }
    }

    @Override
    public boolean shouldTerminate() {
        // TODO shouldTerminate
        return false;
    }


}
