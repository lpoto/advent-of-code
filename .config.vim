let g:collection_c_compiler = "gcc %:p -o %:p:r -std=c99 -Wall -pedantic"
let g:collection_c_execute = "%:p:r"
let g:collection_c_formater = "clang-format -style=file %"

let g:collection_cpp_compiler = "g++ %:p %:p:h:h/utils.c -o %:p:h/__compiled__/%:t:r -std=c++11 -Wall -pedantic"
let g:collection_cpp_execute = "%:p:h/__compiled__/%:t:r %:p:h/inputs/%:t:r.txt"
let g:collection_cpp_formater = "clang-format -style=file %"

let g:collection_errorlist_size = 80

set wildignore+=**.git/**
set wildignore+=**/__compiled__/**
