lua << EOF
vim.fn['telescope_pickers'] = function()
    require("telescope").setup({
        pickers = {
            find_files = {
                theme = "ivy",
                hidden = 1,
                file_ignore_patterns = {
                    "__compiled__",
                    ".git/",
                    "__pycache__/",
                    }
                }
            }
        })
end

vim.fn['program_filetypes'] = function()
    root = require('root')()
    require('program').setup({
        filetypes = {
            cpp = {
                compiler = {
                    exe = 'g++',
                    args = {
                        '%:p',
                        root..'/2020/utils.cpp',
                        '-o '..root..'/2020/__compiled__/%:t:r.out',
                        '-std=c++20',
                        '-Wall',
                        '-pedantic'
                    }
                },
                execution = {
                    args = {
                        root..'/2020/__compiled__/%:t:r.out',
                        root..'/2020/inputs/%:t:r.txt',
                    }
                }
            },
            python = {
                interpreter = {
                    exe = 'python3',
                    args = {
                        root..'/2021/main.py',
                    },
                    end_args = {
                        '%:p:t:r'
                    }
                }
            }
        }
    })
end

vim.fn['formatter'] = function()
    require('formatter').setup({
        filetype = {
            cpp = {
              function()
                return {
                    exe = "clang-format",
                    args = {
                        "--assume-filename",
                        vim.api.nvim_buf_get_name(0)
                    },
                    stdin = true,
                    cwd = require('root')()
                }
              end
            },
            python = {
                function()
                  return {
                    exe = "python3 -m autopep8",
                    args = {
                      "--in-place --aggressive --aggressive --aggressive",
                      vim.fn.fnameescape(vim.api.nvim_buf_get_name(0))
                    },
                    stdin = false
                  }
                end
            }
        }
    })
end
EOF
