#include "../include/Summary.h"
#include "../include/event.h"

void Summary::addEvent(Event &event)
{

    gameEvent gameEvent(event.get_time(), event.get_name(), event.get_description());
    // add the gameEvent to the correct list
    if (event.get_game_updates().at("before halftime") == "true")
    {
        sortedEventInsert(firstHalfEvents, gameEvent);
    }
    else
    {
        sortedEventInsert(secondHalfEvents, gameEvent);
    }

    // update general stats
    for (auto &update : event.get_game_updates()) {
        general_stats[update.first] = update.second;
    }

    // update team a stats
    for (auto &update : event.get_team_a_updates()) {
        team_a_stats[update.first] = update.second;
    }

    // update team b stats
    for (auto &update : event.get_team_b_updates()) {
        team_b_stats[update.first] = update.second;
    }
}

void Summary::printSummary() {
        string summary = team_a_name + " vs " + team_b_name + "\n";
        summary += "Game Stats:\n";
        summary += "General Stats:\n";
        // Probably sorted alphabetically - need to make sure
        for (auto &general_stat: general_stats) {
                summary += general_stat.first + ": " + general_stat.second + "\n";
        }
        summary += "Team A Stats:\n";
        for (auto &team_a_stat: team_a_stats) {
                summary += team_a_stat.first + ": " + team_a_stat.second + "\n";
        }
        summary += "Team B Stats:\n";
        for (auto &team_b_stat: team_b_stats) {
                summary += team_b_stat.first + ": " + team_b_stat.second + "\n";
        }
        summary += "Game Events:\n";
        firstHalfEvents.sort([](gameEvent &a, gameEvent &b) { return a.time < b.time; });
        secondHalfEvents.sort([](gameEvent &a, gameEvent &b) { return a.time < b.time; });
        for (auto &firstHalfEvent: firstHalfEvents) {
                summary += firstHalfEvent.name + " " + to_string(firstHalfEvent.time) + " " +
                           firstHalfEvent.description + "\n";
        }
        for (auto &secondHalfEvent: secondHalfEvents) {
                summary += secondHalfEvent.name + " " + to_string(secondHalfEvent.time) + " " +
                           secondHalfEvent.description + "\n";
        }
}

void Summary::sortedEventInsert(list<gameEvent> eventList, gameEvent event) {

    // first item inserted
    if(eventList.empty()){
        eventList.push_back(event);
    }

    // optimization for last item
    else if (eventList.back().time < event.time){
        eventList.push_back(event);
    }

    else{
        // optimization for deciding whether to start from the start or end
        // based on the average time value
        int avgTime = (eventList.front().time + eventList.back().time)/2;
        if(event.time <= avgTime)
        {
            for(auto it = eventList.begin(); it != eventList.end(); ++it) {
                if (it->time > event.time) {
                    eventList.insert(it, event);
                    return;
                }
            }
        }
        else{
            for(auto it = eventList.rbegin(); it != eventList.rend(); ++it) {
                if (it->time < event.time) {
                    eventList.insert(it.base(), event);
                    return;
                }
            }
        }
    }
}

