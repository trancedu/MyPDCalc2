#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include "Command.h"
#include "UserInterface.h" 

class CommandManager {
public:
    explicit CommandManager(UserInterface& ui) : ui_(ui) {}

    void execute(CommandPtr command) {
        if (!command) return;

        // If we're not at the end, remove the future commands
        if (position_ < commands.size()) {
            commands.erase(commands.begin() + position_, commands.end());
        }

        command->execute();
        commands.push_back(std::move(command));
        position_ = commands.size();
    }

    void undo() {
        if (position_ > 0) {
            position_--;
            if (commands[position_]) {
                commands[position_]->undo();
            }
        }
    }

    void redo() {
        if (position_ < commands.size() && commands[position_]) {
            commands[position_]->execute();
            position_++;
        }
        else {
            ui_.showMessage("Unable to redo");
        }
    }

private:
    UserInterface& ui_;
    std::vector<CommandPtr> commands;
    int position_ = 0;
};
