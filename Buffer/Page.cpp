//
// Created by msumi on 22/05/2024.
//

#include "Page.h"

Page::Page() {
	char c = ' ';
	data = new string(PAGE_SIZE, c);
}

Page::~Page() {
	delete data;
}
