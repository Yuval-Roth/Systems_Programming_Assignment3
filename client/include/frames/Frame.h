#pragma once

using namespace std;

#include "StompCommand.h"
#include <unordered_map>
#include <string>
#include <sstream>

class UserData;

class Frame {
    protected:
        static const string PROTOCOL_VERSION;
        static constexpr char END_OF_FRAME = '\0';
        static constexpr char NEW_LINE = '\n';
        static constexpr char HEADER_DELIMITER = ':';

        Frame () = delete;   
        Frame(StompCommand command, unordered_map<string, string> headers, string frameBody);

        unordered_map<string, string> headers;
        string frameBody;
        StompCommand command;
    private:
        static StompCommand parseCommand(string command);
        static Frame* createFrame(StompCommand command, unordered_map<string, string> headers, string frameBody);
        string commandString(StompCommand command);
    protected:
        static UserData& userData;
    public:
        static Frame* parse(string messageToParse);
        string toString();
        StompCommand getCommand();
        unordered_map<string,string> getHeaders();
        string getFrameBody();
        virtual ~Frame() = default;
};

