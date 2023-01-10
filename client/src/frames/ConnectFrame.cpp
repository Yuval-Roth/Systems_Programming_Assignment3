#include "ConnectFrame.h"

const string USERNAME_HEADER = "username";
const string PASSWORD_HEADER = "password";
const string ACCEPT_VERSION_HEADER = "accept-version";
const string HOST_HEADER = "host";

ConnectFrame::ConnectFrame(StompCommand command, unordered_map<string, string> headers, string frameBody)
    : Frame(command, headers, frameBody){}

Frame *ConnectFrame::get(string host, string username, string password)
{
    unordered_map<string, string> headersMap;
    headersMap[ACCEPT_VERSION_HEADER] = PROTOCOL_VERSION;
    headersMap[HOST_HEADER] = host;
    headersMap[USERNAME_HEADER] = username;
    headersMap[PASSWORD_HEADER] = password;
    StompCommand command = StompCommand::CONNECT;
    string frameBody = "";
    return new ConnectFrame(command, headersMap, frameBody);
}
