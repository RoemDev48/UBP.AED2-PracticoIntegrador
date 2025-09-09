#pragma once
#include <vector>
#include <string>
#include <utility>

class Node
{
public:
    Node();
    virtual ~Node();

    void setParent(Node* parent);
    Node* getParent() const;

    void addChild(Node* child, float distance);
    std::vector<std::pair<Node*, float>>& getChildren();

protected:
    void clearChildren();

private:
    Node* m_parent;
    std::vector<std::pair<Node*, float>> m_children;
};
