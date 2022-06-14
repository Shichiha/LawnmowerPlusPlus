#include <unordered_map>
#include <string_view>
#include <cstring>
#include <dpp/dpp.h>
#include <filesystem>
#include "utils.h"
#include <json.hpp>
#include <MyBot.h>

std::unordered_map<std::string, command_entry> commands;
std::string get_token()
{
    std::string path = std::filesystem::current_path().string();
    std::string file = path + "\\config.json";
    std::ifstream ifs(file);
    if (!ifs.is_open())
    {
        Log("Config not found at %s", file.c_str());
        return "";
    }
    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    nlohmann::json json = nlohmann::json::parse(ss.str());
    return json["token"];
}

int main()
{
    dpp::cluster bot(get_token());
    init_commands(bot);

    bot.on_slashcommand([&bot](const dpp::slashcommand_t &event)
                        {
        commands[event.command.get_command_name()].cb(bot, event);
        Log("%s Called by %s", event.command.get_command_name().c_str(), event.command.usr.username.c_str()); });

    bot.on_ready([&bot](const dpp::ready_t &event)
                 {
        if (dpp::run_once<struct register_bot_commands>())
        {
            for (auto &[name, entry] : commands)
            {
                bot.global_command_create(entry.cmd);
                Log("Registered command %s", name.c_str());
            }
            Log("Registered %d commands", commands.size());
        } });

    Log("Bot Starting...");
    bot.start(false);
}
