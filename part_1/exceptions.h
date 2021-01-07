#include <exception>

namespace mtm{
    class Exception: public std::exception{};

    class InvalidDate: public Exception{};
    class NegativeDays: public Exception{};
    class AlreadyRegistered: public Exception{};
    class NotRegistered: public Exception{};
    class AlreadyInvited: public Exception{};
}