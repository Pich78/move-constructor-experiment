//memory-dump.hpp
#pragma once
#include <string>
#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include "memory-dump.hpp"

void indent(int depth) {
  for(int i = 0; i < depth; ++i)
    printf("  ");
}

template <class T>
void dump_memory(const T * p, size_t items, const char * title, int depth) {
  indent(depth);
  printf("Address: %08x -> %s\n", (unsigned int) p, title);
  // Make a format string that prints hex with correct number of leading zeroes
  std::stringstream sstr;
  sstr << "%0" << sizeof(T) * 2 << "x ";
  std::string format = sstr.str();
  indent(depth + 1);
  const T * end = p + items;
  for(const T * chunk = p; chunk < end; ++chunk) {
    printf(format.c_str(), *chunk);
  }
  printf("\n");
}

// Pretend all pointers are to int to reduce number of casts
template<class T> 
void dump_vtable(const T& t, int virtuals) {
  // In memory, the first bytes of the instance are occupied by the vtable
  int * vtbl = (int *) &t;
  int vtable_size = virtuals * sizeof(int);
  indent(2);
  printf("vtbl (%08x - %08x)", *vtbl, *vtbl + vtable_size - 1);
  printf(" %d entr%s:\n", virtuals, ((virtuals == 1) ? "y" : "ies"));
  for(int i = 0; i < virtuals; ++i) {
    int * fptr = ((int **) vtbl)[i];
    std::stringstream sstr;
    sstr << "fptr " << i << ":";
    dump_memory(fptr, 1, sstr.str().c_str(), 3);
    dump_memory((unsigned char *) *fptr, 16, "implementation (first 16 bytes):", 4);
  }
}

template<class T>
std::string object_size(const T& t) {
  std::stringstream sstr;
  sstr << sizeof(t) << " byte";
  if (sizeof(t) != 1)
    sstr << "s";
  return sstr.str();
}


template<class T> 
void dump_instance(const char * title, const T& t, int virtuals = 0)
{
  std::cout << title << std::endl;
  std::stringstream sstr;
  sstr << "instance (" << object_size(t) << "):";
  dump_memory((unsigned char *) &t, sizeof(t), sstr.str().c_str(), 1);
  if (virtuals > 0)
    dump_vtable(t, virtuals);
  std::cout << std::endl;
}
