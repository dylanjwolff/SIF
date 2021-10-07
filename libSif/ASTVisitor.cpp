#include "ASTVisitor.hpp"
#include <spot/tl/parse.hh>
#include <spot/tl/print.hh>
#include <spot/tl/parse.hh>
#include <spot/twaalgos/translate.hh>
#include <spot/twaalgos/hoa.hh>

namespace Sif
{
    std::string fn_name;

    void before(std::string arg)
    {
        spot::parsed_formula pf = spot::parse_infix_psl("!F(red & X(yellow))");
        if (pf.format_errors(std::cerr))
            std::cout << "ERROR";
        spot::translator trans;
        trans.set_type(spot::postprocessor::Monitor);
        trans.set_pref(spot::postprocessor::Deterministic);
        spot::twa_graph_ptr aut = trans.run(pf.f);
        aut->edge_data(0.);
        print_hoa(std::cout, aut) << '\n';
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
            fn_name = fd->get_name();
            if (fd->function_is_constructor())
            {
                fn_name = "constructor";
            }

            fd->get_params();

            BlockNodePtr block = fd->get_function_body();

            if (block != nullptr)
            {
                ASTNodePtr first = block->get_statement(0);
                ASTNodePtr last = block->get_statement(block->num_statements() - 1);
                if (first != nullptr)
                {
                    first->insert_text_before("B4F" + fn_name);
                }
                if (last != nullptr)
                {
                    last->insert_text_after("AFL" + fn_name);
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
