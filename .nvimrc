lua << EOF
vim.fn['telescope_pickers'] = function()
    require("telescope").setup({
        pickers = {
            find_files = {
                theme = "ivy",
                hidden = 1,
                file_ignore_patterns = {
                    "__compiled__", ".git/"}
                }
            }
        })
end

vim.fn['program_filetypes'] = function()
    require('program').setup({
        filetypes = {
            cpp = {
                compiler = {
                    exe = 'g++',
                    args = {
                        '%:p',
                        '%:p:h:h/utils.cpp',
                        '-o %:p:h/__compiled__/%:t:r',
                        '-std=c++20',
                        '-Wall',
                        '-pedantic'
                    }
                },
                execution = {
                    args = {
                        '%:p:h/__compiled__/%:t:r',
                        '%:p:h:h/inputs/%:t:r.txt'
                    }
                }
            }
        }
    })
end

vim.fn['neoformat_filetypes'] = function()
    local clangopts = "-style='{"..table.concat({
    	"Standard: Cpp11",
    	"IndentWidth: 4",
    	"TabWidth: 4",
    	"ColumnLimit: 80",
    	"SortIncludes: true",
    	"ReflowComments: true",
    	"BreakBeforeBraces: WebKit",
    	"PointerAlignment: Left",
    	"AllowShortLoopsOnASingleLine: true",
    	"AllowShortIfStatementsOnASingleLine: true",
    	"AllowShortFunctionsOnASingleLine: true",
    }, ', ').."}'"

    vim.g['neoformat_enabled_cpp'] = {'clangformat'}
    vim.g['neoformat_cpp_clangformat'] = {
        exe = 'clang-format',
        args = {clangopts}
    }
end
EOF
