package bgu.spl.net.impl.stomp.Backend;

import bgu.spl.net.genericServers.interfaces.ConnectionHandler;
import bgu.spl.net.impl.stomp.Service.interfaces.ChannelsManager;
import bgu.spl.net.impl.stomp.Service.interfaces.ConnectionsManager;
import bgu.spl.net.impl.stomp.StompExceptions.ChannelException;
import bgu.spl.net.impl.stomp.StompExceptions.ConnectionException;


/**
 * This class is the facade of the backend.
 * It implements the ConnectionsManager and ChannelsManager interfaces.
 * It is a singleton class.
 */
public class StompFacade implements ChannelsManager<String>, ConnectionsManager<String> {
    
    private static StompFacade instance = null;
    
    private final UserController uc;
    private final ChannelController cc;
    private final SessionController sc;

    private int connectionIdCounter;
    
    private StompFacade() {
        uc = new UserController();
        cc = new ChannelController();
        sc = new SessionController();

        connectionIdCounter = 0;
    }

    //===============================================================================================|
    //========================== ConnectionManager interface methods ================================|
    //===============================================================================================|

    @Override
    public void connect(ConnectionHandler<String> handler,String username, String password) throws ConnectionException{
        
        if(uc.containsUser(username) == false) {
            uc.addUser(username, password);
        }
        
        uc.login(username, password);
        int connectionId = connectionIdCounter++;
        sc.newSession(handler,connectionId, username);
    }

    @Override
    public void disconnect(ConnectionHandler<String> handler) throws ConnectionException{

        Session session = sc.getSession(handler);
        String username = session.getUsername();
        sc.closeSession(handler);
        uc.logout(username);
    }

    //===============================================================================================|
    //============================== ChannelsManager interface methods ==============================|
    //===============================================================================================|

    @Override
    public void subscribe(ConnectionHandler<String> handler, int subId, String channel) throws ChannelException {
        cc.subscribe(handler, subId, channel);
    }

    @Override
    public void unsubscribe(ConnectionHandler<String> handler, int subId) throws ChannelException {
        cc.unsubscribe(handler, subId);
    }

    @Override
    public void whisper(ConnectionHandler<String> handler, String msg) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void broadcast(String channel, String msg) {
        // TODO Auto-generated method stub
        
    }

    //===============================================================================================|
    //============================== Utility methods ================================================|
    //===============================================================================================|

    /**
     * Validate that the user exists and is logged in
     * @param username
     * @throws ConnectionException
     */
    private void validateUser(String username) throws ConnectionException {
        if(uc.containsUser(username) == false) {
            throw new ConnectionException("User does not exist");
        }
        if(uc.isLoggedIn(username) == false) {
            throw new ConnectionException("User is not logged in");
        }
    }

    /**
     * Singleton instance
     */
    public static StompFacade getInstance() {
        if(instance == null) {
            instance = new StompFacade();
        }
        return instance;
    }
}
