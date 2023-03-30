#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
    private:
      struct Node{
          Node(KeyType cKey, ValueType cValue){
              nKey = cKey;
              nValues.push_back(cValue);
              nLeft = nRight = nullptr;
          }
          KeyType nKey;
          std::vector<ValueType> nValues;
          Node* nLeft;
          Node* nRight;
      };
      Node* m_root;
    
    //recursively traversing the tree and deleting each node
      void freeTree(Node *cur){
          if (cur == nullptr)
              return;
          freeTree(cur->nLeft);
          freeTree (cur->nRight);
          delete cur; 
      }
    public:
        class Iterator
        {
          public:
            Iterator(){
                m_index = -1;
            }
            
            Iterator(Node* ptr){
                keyValues = &(ptr->nValues);
                m_index = 0;
            }

            ValueType& get_value() const
            {
                return (*keyValues).at(m_index);
            }

            bool is_valid() const
            {
                return (m_index != -1);
            }

            void advance()
            {
                if (m_index+1 >= keyValues->size())
                    m_index = -1;
                else
                    m_index++;
            }

          private:
            KeyType m_key;
            std::vector<ValueType>* keyValues;
            int m_index;
        };

        TreeMultimap()
        {
            m_root = nullptr;
        }

        ~TreeMultimap()
        {
            Node* cur = m_root;
            freeTree(cur);
        }

        void insert(const KeyType& key, const ValueType& value)
        {
            if (m_root == nullptr)
                { m_root = new Node(key, value); return; }
            Node* cur = m_root;
            //progressing through each left and right subtree of every node to find insert position
            for (;;){
                if (key == cur->nKey) {
                    cur->nValues.push_back(value);
                    return;
                }
                if (key < cur->nKey) {
                    if (cur->nLeft != nullptr)
                        cur = cur->nLeft;
                    else {
                        cur->nLeft = new Node(key, value);
                        return;
                    }
                }
                else if (key > cur->nKey) {
                    if (cur->nRight != nullptr)
                        cur = cur->nRight;
                    else{
                        cur->nRight = new Node(key, value);
                        return;
                    }
                }
            }
        }

        Iterator find(const KeyType& key) const
        {
            //returning iterator once key is found at left/right subtree
            Node *cur = m_root;
            while (cur != nullptr){
                if (key == cur->nKey)
                    return Iterator(cur);
                else if (key < cur->nKey)
                    cur = cur->nLeft;
                else
                    cur = cur->nRight;
            }
            return Iterator();
        }
};

#endif // TREEMULTIMAP_INCLUDED
