//Item.hpp
#pragma once
#include <string>
#include <iostream>
#include <algorithm>

// Representation of an item database row <itemID><itemName><itemValue>

class Item {
    
    public:
        Item(uint32_t itemID, const std::string itemName, uint32_t itemValue) :
            _itemId(itemID),
            _itemName(itemName),
            _itemValue(itemValue)
            {
                std::cout << "Item: " << _itemName << " created. Item ID address = " << &_itemId << std::endl;
            };
        
        ~Item(void)
        {
            std::cout << "Item: " << _itemName << " destroyed. Item ID address = " << &_itemId << std::endl;
        }

        Item(const Item& other) :
            _itemId(other._itemId),
            _itemName(other._itemName),
            _itemValue(other._itemValue)
            {
                std::cout << "Item: " << _itemName << " copy created. Item ID address = " << &_itemId << std::endl;
            };

        Item& operator=(const Item& other)
        {

            if (this != &other)
            {
                _itemId = other._itemId;
                _itemName = other._itemName;
                _itemValue = other._itemValue;
            }
            std::cout << "Item: " << _itemName << " copy assigned. Item ID address = " << &_itemId << std::endl;
            return *this;             
        }

        Item(Item&& other) noexcept :
            _itemId(0),
            _itemName(""),
            _itemValue(0)

        {
            std::cout << "Item: " << other._itemName << " moved. Item ID address = " << &(other._itemId) << std::endl;
            _itemId = other._itemId;
            _itemName = other._itemName;
            _itemValue = other._itemValue;

            other._itemId = 0;
            other._itemName = "";
            other._itemValue = 0;
        };

        Item& operator=(Item&& other) noexcept
        {

            if (this != &other)
            {
                _itemId = other._itemId;
                _itemName = other._itemName;
                _itemValue = other._itemValue;

                other._itemId = 0;
                other._itemName = "";
                other._itemValue = 0;

            }
            std::cout << "Item: " << _itemName << " move assigned. Item ID address = " << &(other._itemId) << std::endl;
            return *this;             
        }
           
        uint32_t getID(void)
        {
            return _itemId;
        }
        
        std::string getName(void)
        {
            return _itemName;
        }

        uint32_t getValue(void)
        {
            return _itemValue;
        }

        void setValue(uint32_t itemValue)
        {
            _itemValue = itemValue;
        }

        uint32_t _itemId;   // Should be private: made public for memory dumping purposes
    private:
        
        std::string _itemName;
        uint32_t _itemValue;


};