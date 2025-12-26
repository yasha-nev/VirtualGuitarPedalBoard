
#include "ChorusPedal.hpp"
#include "Core.hpp"
#include "DelayPedal.hpp"
#include "DistortionPedal.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <sstream>
#include <vector>

static std::vector<std::string> split(const std::string& line) {
    std::istringstream iss(line);
    return { std::istream_iterator<std::string> { iss }, std::istream_iterator<std::string> {} };
}

static void printStringList(const std::list<std::string>& list) {
    for(const auto& el: list) {
        std::cout << el << "\n";
    }
}

static void printPedals(Core& core) {
    auto& pedals = core.getPedals();

    if(pedals.empty()) {
        std::cout << "(empty)\n";
        return;
    }

    for(size_t i = 0; i < pedals.size(); ++i) {

        if(!pedals[i].get()) {
            continue;
        }

        std::cout << i << ": ";

        switch(pedals[i]->getType()) {
            case PedalType::DISTORTION:
                std::cout << "Distortion";
                break;
            case PedalType::DELAY:
                std::cout << "Delay";
                break;
            case PedalType::CHORUS:
                std::cout << "Chorus";
                break;
            case PedalType::BASE:
                std::cout << "default";
                break;
            default:
                break;
        }

        std::cout << (pedals[i]->isActive() ? " [ON]" : " [OFF]") << "\n";
    }
}

static void addPedal(Core& core, const std::string& type, size_t index) {
    auto& pedals = core.getPedals();

    if(index > pedals.size()) {
        return;
    }

    if(type == "distortion") {
        core.insertPedalByIndex(std::make_unique<DistortionPedal>(0.5f, 0.5f, 0.5f), index);
    } else if(type == "delay") {
        core.insertPedalByIndex(std::make_unique<DelayPedal>(0.3f, 0.4f, 0.5f), index);
    } else if(type == "chorus") {
        core.insertPedalByIndex(std::make_unique<ChorusPedal>(0.8f, 0.5f), index);
    }
}

static void setParam(Core& core, size_t index, const std::string& param, float value) {
    auto& pedals = core.getPedals();

    if(index >= pedals.size()) {
        return;
    }

    auto* pedal = pedals[index].get();

    switch(pedal->getType()) {
        case PedalType::DISTORTION: {
            auto* p = dynamic_cast<DistortionPedal*>(pedal);
            if(param == "gain") {
                p->setDist(value);
            }
            if(param == "tone") {
                p->setTone(value);
            }
            if(param == "level") {
                p->setLevel(value);
            }
            break;
        }
        case PedalType::DELAY: {
            auto* p = dynamic_cast<DelayPedal*>(pedal);
            if(param == "time") {
                p->setTime(value);
            }
            if(param == "feedback") {
                p->setFeedback(value);
            }
            if(param == "level") {
                p->setLevel(value);
            }
            break;
        }
        case PedalType::CHORUS: {
            auto* p = dynamic_cast<ChorusPedal*>(pedal);
            if(param == "rate") {
                p->setRate(value);
            }
            if(param == "depth") {
                p->setDepth(value);
            }
            break;
        }
        case PedalType::BASE:
        default: {
            std::cout << "no correct pedal type\n";
            break;
        }
    }
}

static void CLI(Core& core) {
    std::string line;

    std::cout << "VGP CLI — type 'help'\n";

    while(true) {
        std::cout << "> ";
        if(!std::getline(std::cin, line)) {
            break;
        }

        auto args = split(line);
        if(args.empty()) {
            continue;
        }

        if(args[0] == "exit") {
            core.stop();
            break;
        } else if(args[0] == "help") {
            std::cout << "devices in|out\n"
                         "use in|out <name>\n"
                         "start | stop\n"
                         "pedals\n"
                         "add <distortion|delay|chorus> <index>\n"
                         "remove <index>\n"
                         "toggle <index>\n"
                         "set <index> <param> <value>\n"
                         "exit\n";
        } else if(args[0] == "devices") {
            if(args.size() < 2) {
                continue;
            }
            if(args[1] == "in") {
                printStringList(core.getInputDeviceList());
            } else if(args[1] == "out") {
                printStringList(core.getOutputDeviceList());
            }
        } else if(args[0] == "use") {
            if(args.size() < 3) {
                continue;
            }
            if(args[1] == "in") {
                core.chooseInputDevice(args[2]);
            } else if(args[1] == "out") {
                core.chooseOutputDevice(args[2]);
            }
        } else if(args[0] == "start") {
            core.start();
        } else if(args[0] == "stop") {
            core.stop();
        } else if(args[0] == "pedals") {
            printPedals(core);
        } else if(args[0] == "add") {
            if(args.size() >= 3) {
                addPedal(core, args[1], std::stoul(args[2]));
            }
        } else if(args[0] == "remove") {
            if(args.size() >= 2) {
                long index = std::stoul(args[1]);
                core.deletePedalByIndex(index);
            }
        } else if(args[0] == "toggle") {
            if(args.size() >= 2) {
                size_t i = std::stoul(args[1]);
                auto& pedals = core.getPedals();
                if(i < pedals.size()) {
                    pedals[i]->tongle();
                }
            }
        } else if(args[0] == "set") {
            if(args.size() >= 4) {
                setParam(core, std::stoul(args[1]), args[2], std::stof(args[3]));
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Usage: vgp <path/to/plugins>\n";
        return 0;
    }

    Core core(argv[1]);

    CLI(core);
    return 0;
}
