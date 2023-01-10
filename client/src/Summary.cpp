#include "../include/Summary.h"
#include "../include/event.h"

Summary::Summary(string userName) : userName(userName) {}

void Summary::addEvent(Event &event) {
        gameEvent gameEvent(event.get_time(), event.get_name(), event.get_description());
        if (event.get_game_updates().at("before halftime") == "true") {
                firstHalfEvents.push_back(gameEvent);
        } else {
                secondHalfEvents.push_back(gameEvent);
        }
}

void Summary::printSummary() {
        string summary = team_a_name + " vs " + team_b_name + "\n";
        summary += "Game Stats:\n";
        summary += "General Stats:\n";
        for (auto &general_stat : general_stats) {
                summary += general_stat.first + ": " + general_stat.second + "\n";
        }
        summary += "Team A Stats:\n";
        for (auto &team_a_stat : team_a_stats) {
                summary += team_a_stat.first + ": " + team_a_stat.second + "\n";
        }
        summary += "Team B Stats:\n";
        for (auto &team_b_stat : team_b_stats) {
                summary += team_b_stat.first + ": " + team_b_stat.second + "\n";
        }
        summary += "Game Events:\n";
        firstHalfEvents.sort([](gameEvent &a, gameEvent &b) { return a.time < b.time; });
        secondHalfEvents.sort([](gameEvent &a, gameEvent &b) { return a.time < b.time; });
        for (auto &firstHalfEvent : firstHalfEvents) {
                summary += firstHalfEvent.name + " " + to_string(firstHalfEvent.time) + " " + firstHalfEvent.description + "\n";
        }
        for (auto &secondHalfEvent : secondHalfEvents) {
                summary += secondHalfEvent.name + " " + to_string(secondHalfEvent.time) + " " + secondHalfEvent.description + "\n";
        }
}
