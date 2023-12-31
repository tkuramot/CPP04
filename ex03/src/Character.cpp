/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:25:53 by tkuramot          #+#    #+#             */
/*   Updated: 2023/11/23 13:57:36 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by k.t. on 2023/11/01.
//

#include "AMateria.hpp"
#include "Character.hpp"
#include <iostream>
#include <string>

Character::Character(const std::string &name) : name_(name) {
  std::cout << "Character constructor called" << std::endl;
  for (int i = 0; i < kMaxSlots; ++i) {
	inventory_[i] = NULL;
	is_equipped_[i] = false;
  }
}

Character::Character(const Character &obj) : name_(obj.name_) {
  std::cout << "Character copy constructor called" << std::endl;
  for (int i = 0; i < kMaxSlots; ++i) {
	if (is_equipped_[i]) {
	  inventory_[i] = obj.inventory_[i]->clone();
	} else {
	  inventory_[i] = NULL;
	}
	is_equipped_[i] = obj.is_equipped_[i];
  }
}

Character::~Character() {
  std::cout << "Character destructor called" << std::endl;
  for (int i = 0; i < kMaxSlots; ++i) {
	if (is_equipped_[i]) {
	  delete inventory_[i];
	}
  }
}

Character &Character::operator=(const Character &obj) {
  if (this == &obj) {
	return *this;
  }
  name_ = obj.name_;
  for (int i = 0; i < kMaxSlots; ++i) {
	AMateria *temp_inventory = NULL;
	bool temp_is_equipped = false;
	if (is_equipped_[i]) {
	  temp_inventory = obj.inventory_[i]->clone();
	  temp_is_equipped = obj.is_equipped_[i];
	  delete inventory_[i];
	  is_equipped_[i] = false;
	}
	inventory_[i] = temp_inventory;
	is_equipped_[i] = temp_is_equipped;
  }
  return *this;
}

std::string const &Character::GetName() const {
  return name_;
}

void Character::equip(AMateria *materia) {
  for (int i = 0; i < kMaxSlots; ++i) {
	if (!is_equipped_[i]) {
	  is_equipped_[i] = true;
	  inventory_[i] = materia;
	  std::cout << "Character " << GetName() << " equipped " << materia->GetType() << " at slot " << i << std::endl;
	  return;
	}
  }
  std::cout << "Character " << GetName() << " does not have any empty slot!" << std::endl;
}

void Character::unequip(int idx) {
  if (idx < 0 || idx >= kMaxSlots) {
	throw std::out_of_range("Character slot index out of range");
  }
  inventory_[idx] = NULL;
  is_equipped_[idx] = false;
}

void Character::use(int idx, ICharacter &target) {
  if (idx < 0 || idx >= kMaxSlots) {
	throw std::out_of_range("Character slot index out of range");
  }
  if (!is_equipped_[idx]) {
	std::cout << "Character " << GetName() << " does not have any item in slot " << idx << "!" << std::endl;
	return;
  }
  inventory_[idx]->use(target);
}