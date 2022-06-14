#include <dpp/dpp.h>
#include <filesystem>
#include "helpers.h"
#include <json.hpp>
#include "includes.h"

std::filesystem::path config_path = "./config.json";
typedef void (*commandptr)(dpp::cluster& bot, const dpp::slashcommand_t& event);
typedef struct {
    std::string desc;
    commandptr cmd;
} command_entry;
std::unordered_map<std::string, command_entry> commands;
const std::string get_token() {
    if (std::filesystem::exists(config_path)) {
        std::ifstream ifs(config_path);
        nlohmann::json j;
        ifs >> j;
        const std::string BOT_TOKEN = j["token"];
        return BOT_TOKEN;
    }
    else {
        Log("Config Not found");
        return "";
    }
}

#include <string_view>
#include <cstring>

static size_t hash_cstr(const char* s)
{
    return std::hash<std::string_view>()(std::string_view(s, std::strlen(s)));
}
void ping_cmd(dpp::cluster& bot, const dpp::slashcommand_t& event)
{
    event.reply("Pong!");
}
void hi_cmd(dpp::cluster& bot, const dpp::slashcommand_t& event)
{
    event.reply("hi!");
}
bool register_command(std::string name, std::string desc, commandptr func)
{
    if (commands.count(name)) return false;
    commands[name] = { desc, func };
    return true;
}

int main() {
    dpp::cluster bot(get_token());
    register_command("ping", "Ping Pong!", ping_cmd);
    register_command("hi", "amongus", hi_cmd);
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        auto cmd_name = event.command.get_command_name();
        if (commands.count(cmd_name))
            commands[cmd_name].cmd(bot, event);
        });
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            for (auto& [name, entry] : commands)
            {
                bot.global_command_create(
                    dpp::slashcommand(name, entry.desc, bot.me.id)
                );
            }
        }
        });
    bot.start(false);
}
