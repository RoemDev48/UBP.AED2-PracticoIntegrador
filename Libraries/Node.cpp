#include "./Node.h"

Node::Node() : m_parent(nullptr) {}
Node::~Node() {}

void Node::setParent(Node* parent) { m_parent = parent; }
Node* Node::getParent() const { return m_parent; }

void Node::addChild(Node* child, float distance)
{
    m_children.push_back(std::make_pair(child, distance));
}

std::vector<std::pair<Node*, float>>& Node::getChildren() { return m_children; }
void Node::clearChildren() { m_children.clear(); }
