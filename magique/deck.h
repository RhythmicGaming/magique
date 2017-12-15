//
// Created by Don Goodman-Wilson on 14/11/2017.
//

#pragma once

#include <string>
#include <vector>
#include <map>
#include <json.hpp>
#include "card.h"
#include "catalog.h"
#include "collection.h"
#include "interactions.h"

namespace magique
{

class deck;

void to_json(nlohmann::json &j, const deck &p);

void from_json(const nlohmann::json &j, deck &p);

class deck
{
public:
    deck(const std::string &filename, const catalog &catalog, interactions interactions); //TOOD we might need to do something better than a copy here!

    deck(const std::vector<uint64_t> &indices, const collection &collection, interactions interactions);

    static void add_key_card(card key)
    {
        key_cards_.push_back(key);
    }


    double evaluate();

    friend void to_json(nlohmann::json &j, const deck &p);

    friend void from_json(const nlohmann::json &j, deck &p);

public:
    const interactions interactions_;
    std::vector<card> cards_;
    double rank_;
    nlohmann::json reasons_;
    static std::vector<card> key_cards_;
};


} //namespace magique
