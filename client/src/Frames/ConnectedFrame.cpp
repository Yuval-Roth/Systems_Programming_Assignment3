#include "ConnectedFrame.h"

ConnectedFrame::ConnectedFrame(StompCommand command, unordered_map<string, string> headers, string frameBody)
    : Frame(command, headers, frameBody)
{
}