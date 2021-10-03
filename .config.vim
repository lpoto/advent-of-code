let g:collection_cpp_compiler = "g++ %:p %:p:h:h/utils.cpp -o %:p:h/__compiled__/%:t:r -std=c++20 -Wall -pedantic"
let g:collection_cpp_execute = "%:p:h/__compiled__/%:t:r %:p:h/inputs/%:t:r.txt"
let g:collection_cpp_formater = "clang-format -style=file %"

let g:collection_errorlist_size = 80

set wildignore+=**.git/**
set wildignore+=**/__compiled__/**
