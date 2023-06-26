#ifndef TRAGLODIT501_COMMAND_H
#define TRAGLODIT501_COMMAND_H

#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <utility>

#include "../exceptions/exceptions.h"

class Command {
private:
    std::string use;
    std::vector<Command> subCmds;
    std::function<void()> run = nullptr;

    int argc = 0;
    char **argv;

    bool withStringFlag = false;
    std::tuple<std::string, std::string, std::string*> stringFlag;
public:

    Command(std::string use) : use(std::move(use)) {};

    Command(std::string use, int argc, char *argv[]) : use(std::move(use)), argc(argc), argv(argv) {};

    Command(std::string use, std::function<void()> run) : use(std::move(use)), run(std::move(run)) {};

    void registerCommand(Command& cmd) {
        this->subCmds.push_back(cmd);
    }

    std::string getUse() const { return this->use; }

    void stringVar(const std::string& name, const std::string& shortName, std::string *dest) {
        this->stringFlag = std::tuple<std::string, std::string, std::string*>(name, shortName, dest);
        this->withStringFlag = true;
    }

    void execute() {
        int shift = 1;
        if (this->withStringFlag) {
            if (this->argc < 3 ||
                ("--" + std::get<0>(this->stringFlag) != argv[1] &&
                 "-" + std::get<1>(this->stringFlag) != argv[1])) {
                throw FlagRequiredException(std::get<0>(this->stringFlag));
            }
            *std::get<2>(this->stringFlag) = std::string(argv[2]);
            shift += 2;
        }
        if (argc - shift == 0) {
            if (this->run == nullptr) {
                throw NotEnoughArguments();
            }
            this->run();
            return;
        }

        for (auto cmd: this->subCmds) {
            if (cmd.getUse() == argv[shift]) {
                cmd.argc = this->argc - shift;
                cmd.argv = this->argv + shift;
                cmd.execute();
                return;
            }
        }
        throw UnknownArgumentException(argv[1]);
    }
};


#endif //TRAGLODIT501_COMMAND_H
