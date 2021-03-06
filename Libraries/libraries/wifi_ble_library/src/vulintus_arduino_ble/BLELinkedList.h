/*
  This file is part of the ArduinoBLE library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
    This version of the file has been modified to be a part of the 
    Vulintus Arduino BLE library.
*/

#ifndef VULINTUS_ARDUINO_BLE_LINKED_LIST
#define VULINTUS_ARDUINO_BLE_LINKED_LIST

#include <stddef.h>

namespace VulintusArduinoBLE
{
    template<class T> struct BLELinkedListNode
    {
        T data;
        BLELinkedListNode<T>* next;
    };

    template <typename T> class BLELinkedList 
    {
        public:
            BLELinkedList();
            ~BLELinkedList();

            void add(T);
            T get(unsigned int index) const;
            void clear();
            T remove(unsigned int index);

            unsigned int size() const;

        private:
            unsigned int _size;
            BLELinkedListNode<T>* _root;
            BLELinkedListNode<T>* _last;
    };

    /// <summary>
    /// Constructor
    /// </summary>
    template <typename T> BLELinkedList<T>::BLELinkedList() 
        : _size(0), _root(NULL), _last(NULL)
    {
        //empty
    }

    /// <summary>
    /// Destructor
    /// </summary>
    template <typename T> BLELinkedList<T>::~BLELinkedList()
    {
        clear();
    }

    /// <summary>
    /// Add an item to the linked list
    /// </summary>
    template <typename T> void BLELinkedList<T>::add(T item)
    {
        BLELinkedListNode<T>* itemNode = new BLELinkedListNode<T>();

        itemNode->data = item;
        itemNode->next = NULL;

        if (_root == NULL) 
        {
            _root = itemNode;
        } 
        else 
        {
            _last->next = itemNode;
        }

        _last = itemNode;

        _size++;
    }

    /// <summary>
    /// Retrieve an item from the list at the specified index
    /// </summary>
    template <typename T> T BLELinkedList<T>::get(unsigned int index) const
    {
        if (index >= _size) 
        {
            return T();
        }

        BLELinkedListNode<T>* itemNode = _root;

        for (unsigned int i = 0; i < index; i++) 
        {
            itemNode = itemNode->next;
        }

        return itemNode->data;
    }

    /// <summary>
    /// Clear the list
    /// </summary>
    template <typename T> void BLELinkedList<T>::clear()
    {
        BLELinkedListNode<T>* itemNode = _root;

        for (unsigned int i = 0; i < _size; i++) 
        {
            BLELinkedListNode<T>* n = itemNode;
            itemNode = itemNode->next;
            delete n;
        }

        _size = 0;
        _root = NULL;
        _last = NULL;
    }

    /// <summary>
    /// Returns the number of elements in the linked list
    /// </summary>
    template <typename T> unsigned int BLELinkedList<T>::size() const
    {
        return _size;
    }

    /// <summary>
    /// Remove the item at the specified index from the list
    /// </summary>
    template <typename T> T BLELinkedList<T>::remove(unsigned int index)
    {
        if (index >= _size) 
        {
            return T();
        }

        BLELinkedListNode<T>* previousItemNode = NULL;
        BLELinkedListNode<T>* itemNode = _root;

        for (unsigned int i = 0; i < index; i++) 
        {
            previousItemNode = itemNode;
            itemNode = itemNode->next;
        }

        T result = itemNode->data;

        if (previousItemNode == NULL) 
        {
            _root = itemNode->next;
        } 
        else 
        {
            previousItemNode->next = itemNode->next;
        }

        if (_last == itemNode) 
        {
            _last = previousItemNode;
        }

        delete itemNode;
        _size--;

        return result;
    }
}

#endif /* VULINTUS_ARDUINO_BLE_LINKED_LIST */
