#pragma once
#include <discord.hpp>
#include <nlohmann/json.hpp>

#include "utility.hpp"

#include <channel.hpp>
#include <role.hpp>
#include <member.hpp>
#include <emoji.hpp>


discord::Guild::Guild(discord_id id) : discord::Object(id) {}

discord::Guild::Guild(std::string guild_create_event){
    json guild = json::parse(guild_create_event)["d"];

    for (auto& each : guild["members"]){
        discord::Member member{each.dump(), discord::User(each["user"].dump())};
        members.push_back(member);
        if (each["id"] == guild["owner_id"]){
            owner = member;
        }
    }

    // "owner_id": "553478921870508061",
    splash = get_value(guild, "splash", 0);
    mfa_level = get_value(guild, "mfa_level", 0);
    afk_timeout = get_value(guild, "afk_timeout", 0);
    member_count = get_value(guild, "member_count", 0);
    verification_level = get_value(guild, "verification_level", 0);
    explicit_content_filter = get_value(guild, "explicit_content_filter", 0);

    large = get_value(guild, "large", true);
    unavailable = get_value(guild, "unavailable", false);

    std::string temp_id = guild["id"];
    id = std::stoul(temp_id);
    std::string temp_app_id = get_value(guild, "application_id", "0");
    application_id = std::stoul(temp_app_id);

    name = guild["name"];
    icon = get_value(guild, "icon", "");
    region = guild["region"];
    banner = get_value(guild, "banner", "");
    created_at = guild["joined_at"];
    vanity_url_code = get_value(guild, "vanity_url_code", "");
}
