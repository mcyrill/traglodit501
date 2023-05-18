#ifndef TRAGLODIT501_EXCEPTIONS_H
#define TRAGLODIT501_EXCEPTIONS_H

#include "exception"
#include "string"

class UnknownArgumentException : public std::exception {
private:
    std::string msg;
public:
    UnknownArgumentException(const std::string &argName) : msg("Unknown argument: " + argName) {}

    const char *what() const noexcept override {
        return msg.c_str();
    }
};

class NotEnoughArguments : public std::exception {
private:
    std::string msg = "Not enough argument. Example: traglodit501 encode file.txt";
public:
    const char *what() const noexcept override {
        return msg.c_str();
    }
};

class FileNotFound : public std::exception {
private:
    std::string msg;
public:
    FileNotFound(const std::string &filename) : msg("File not found: " + filename) {}

    const char *what() const noexcept override {
        return msg.c_str();
    }
};

class FlagRequiredException : public std::exception {
private:
    std::string msg;
public:
    FlagRequiredException(const std::string &flagName) : msg("Flag --" + flagName + " required") {}

    const char *what() const noexcept override {
        return msg.c_str();
    }
};

class FileNotFoundException : public std::exception {
private:
    std::string msg;
public:
    FileNotFoundException(const std::string &filename) : msg("File " + filename + " not found") {}

    const char *what() const noexcept override {
        return msg.c_str();
    }
};

class CouldNotDecodeException : public std::exception {
private:
    std::string msg;
public:
    CouldNotDecodeException(const std::string &filename) : msg("Could not decode " + filename) {}

    const char *what() const noexcept override {
        return msg.c_str();
    }
};



#endif //TRAGLODIT501_EXCEPTIONS_H
