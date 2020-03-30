#pragma once
#include "PriorityElements.hpp"
#include <string>

class PriorityMapNode {
public:
	int key_;
	PriorityElements* value_;

	PriorityMapNode* next_;

	PriorityMapNode(int k, PriorityElements* v) {
		this->key_ = k;
		this->value_ = v;
		this->next_ = nullptr;
	}
};