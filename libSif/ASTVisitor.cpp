#include "ASTVisitor.hpp"

namespace Sif
{

    void before(std::string arg)
    {
        return;
    }

    void visit(ASTNode *node)
    {
        if (node->get_node_type() == NodeTypeAssignment)
        {
            AssignmentNode *assign = (AssignmentNode *)node;
            ASTNodePtr left_node = assign->get_left_hand_operand();
            if (left_node->get_node_type() == NodeTypeIdentifier)
            {
                IdentifierNodePtr id = std::dynamic_pointer_cast<IdentifierNode>(left_node);
                std::cout << id->get_name() << "\n";
            }
            else if (left_node->get_node_type() == NodeTypeIndexAccess)
            {
                IndexAccessNodePtr ia = std::dynamic_pointer_cast<IndexAccessNode>(left_node);
            }
        }
        else if (node->get_node_type() == NodeTypeFunctionDefinition)
        {
            FunctionDefinitionNode *fd = (FunctionDefinitionNode *)node;
            std::cout << "FN: " << fd->get_name() << "\n";
            BlockNodePtr block = fd->get_function_body();

            if (block != nullptr)
            {
                ASTNodePtr first = block->get_statement(0);
                ASTNodePtr last = block->get_statement(block->num_statements() - 1);
                if (first != nullptr)
                {
                    first->insert_text_before("B4F");
                }
                if (last != nullptr)
                {
                    last->insert_text_after("AFL");
                }
            }
        }
        else if (node->get_node_type() == NodeTypeReturn)
        {
        }
    }

    void after()
    {
        return;
    }

}
