//
// Created by Don Goodman-Wilson on 14/11/2017.
//

#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <nlohmann/json.hpp>
#include "card.h"
#include "catalog.h"
#include "collection.h"
#include "interactions.h"
#include "evaluators/types.h"

namespace magique
{

class deck;

void to_json(nlohmann::json &j, const deck &p);

void from_json(const nlohmann::json &j, deck &p);

class deck
{
public:
    deck(std::vector<uint64_t> indices);

    static void add_key_card(card *key)
    {
        key->bonus_multiplier = 2.0;
        key_cards_.push_back(key);
    }

    double evaluate()
    { return rank_; }

    friend void to_json(nlohmann::json &j, const deck &p);

    friend void from_json(const nlohmann::json &j, deck &p);

    static uint16_t colors;
    static std::unordered_set<card::color> color_identity;
    static collection collection;

    static uint16_t deck_minimum;

    static card::format format;

    static void add_evaluator(evaluators::card_evaluator eval_func)
    {
        card_evaluators_.emplace_back(eval_func);
    }

    static void add_evaluator(evaluators::card_pair_evaluator eval_func)
    {
        card_pair_evaluators_.emplace_back(eval_func);
    }

    static void add_evaluator(evaluators::deck_evaluator eval_func)
    {
        deck_evaluators_.emplace_back(eval_func);
    }

private:
    static std::vector<evaluators::card_evaluator> card_evaluators_;
    static std::vector<evaluators::card_pair_evaluator> card_pair_evaluators_;
    static std::vector<evaluators::deck_evaluator> deck_evaluators_;
    static std::vector<card *> key_cards_;

    //TODO use set or multiset, and count the copies of each card.
    std::unordered_map<std::string, std::pair<uint16_t, card *>> cards_;
    double rank_;
    nlohmann::json reasons_;

    void build_proposed_deck_(std::vector<uint64_t> indices);
};


} //namespace magique
