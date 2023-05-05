#ifndef TRAGLODIT501_COMMAND_H
#define TRAGLODIT501_COMMAND_H

#include <string>
#include <vector>
#include <functional>
#include <utility>
#include "../exceptions/exceptions.h"

class Command {
private:
    std::string use;
    std::vector<Command *> subCmds;
    std::function<void()> run = nullptr;

    int argc = 0;
    char **argv;

    bool withStringFlag = false;
    std::tuple<std::string, std::string, std::string*> stringFlag;
public:

    Command(std::string use) : use(use) {};

    Command(std::string use, int argc, char *argv[]) : use(use), argc(argc), argv(argv) {};

    Command(std::string use, std::function<void()> run) : use(use), run(run) {};

    void registerCommand(Command* cmd) {
        this->subCmds.push_back(cmd);
    }

    std::string getUse() const { return this->use; }

    void stringVar(const std::string& name, const std::string& shortName, std::string *dest) {
        this->stringFlag = std::tuple<std::string, std::string, std::string*>(name, shortName, dest);
        this->withStringFlag = true;
    }

    void execute() {
        int shift = 0;
        if (this->withStringFlag) {
            if (this->argc < 3 ||
                ("--" + std::get<0>(this->stringFlag) != argv[1] &&
                 "-" + std::get<1>(this->stringFlag) != argv[1])) {
                throw FlagRequiredException(std::get<0>(this->stringFlag));
            }
            *std::get<2>(this->stringFlag) = std::string(argv[2]);
            shift += 2;
        }
        if (argc - shift == 1) {
            if (this->run == nullptr) {
                throw NotEnoughArguments();
            }
            this->run();
            return;
        }

        for (auto cmd: this->subCmds) {
            if (cmd->getUse() == argv[shift + 1]) {
                cmd->argc = this->argc - 1 - shift;
                cmd->argv = this->argv + 1 + shift;
                cmd->execute();
                return;
            }
        }
        throw UnknownArgumentException(argv[0]);
    }
};


#endif //TRAGLODIT501_COMMAND_H
