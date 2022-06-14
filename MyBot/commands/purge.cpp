#include <commands/purge.h>

void purge_cmd(dpp::cluster& bot, const dpp::slashcommand_t& event)
{
	auto amount = std::get<std::int64_t>(event.get_parameter("amount"));

	bot.messages_get(event.command.channel_id, 0, 0, 0, amount, [&bot, &event](const dpp::confirmation_callback_t& cc) {
		if (!cc.is_error()) {
			dpp::message_map mm = std::get<dpp::message_map>(cc.value);

			if (mm.size()) {
				std::vector<dpp::snowflake> msg_ids;
				std::transform(mm.begin(), mm.end(), std::back_inserter(msg_ids), [] (const auto& pair) { return pair.first; });
				bot.message_delete_bulk(msg_ids, event.command.channel_id);
			}
		}
	});

    event.reply(dpp::message("Success!").set_flags(dpp::message_flags::m_ephemeral));
}

dpp::slashcommand purge_cmd_init(dpp::cluster& bot)
{
	return dpp::slashcommand()
		.set_name("purge")
		.set_description("Deletes x amount of messages")
		.set_application_id(bot.me.id)
		.add_option(dpp::command_option(dpp::co_integer, "amount", "Amount of messages to delete"));
}
