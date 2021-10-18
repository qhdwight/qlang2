#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/analyze.hpp>
#include <llvm/IR/Constants.h>
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

namespace q2 {
    using namespace TAO_PEGTL_NAMESPACE;

    struct ws : one<' ', '\t', '\n', '\r'> {
    };

    struct sign : one<'+', '-'> {
    };

    struct integer : seq<opt<sign>, plus<digit> > {
    };

    struct ident : plus<sor<alpha, one<'_'>>> {
    };

    struct sig : seq<keyword<'f', 'u', 'n'>, plus<ws>, ident> {
    };

    struct decl : seq<keyword<'i', 'n', 't'>, plus<ws>, ident, plus<ws>, one<'='>, plus<ws>, integer> {
    };

    struct expr : sor<decl> {
    };

    struct func : seq<sig, plus<ws>, one<'{'>, plus<ws>, plus<expr>, plus<ws>, one<'}'>> {
    };

    struct grammar : seq<func, eof> {
    };

//    template<typename Rule>
//    using selector = parse_tree::selector<
//            Rule,
//            parse_tree::store_content::on<func>>;

    enum class type {
        func
    };

    struct entry {
        type type;
    };

    struct state {
        std::vector<entry> stack;
    };

    template<typename Rule>
    struct action {
    };

    template<>
    struct action<decl> {
        template<typename ActionInput>
        static void apply(ActionInput const &in, state &state) {
            std::cout << in.string() << std::endl;
        }
    };
}

int main(int argc, char **argv) {
    namespace peg = TAO_PEGTL_NAMESPACE;

    if (argc <= 1 || peg::analyze<q2::grammar>()) {
        std::cerr << "Too few arguments" << std::endl;
        return EXIT_FAILURE;
    }

    q2::state state;
    peg::file_input in(argv[1]);
    try {
        peg::parse<q2::grammar, q2::action>(in, state);
    }
    catch (peg::parse_error const &e) {
        auto const p = e.positions().front();
        std::cerr << e.what() << '\n'
                  << in.line_at(p) << '\n'
                  << std::setw(p.column) << '^' << '\n';
    }

    return EXIT_SUCCESS;
}
