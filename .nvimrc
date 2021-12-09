let g:telescope_ignore_patterns = ['__compiled__', '.git/', '__pycache__']
let g:telescope_previewer = v:true

lua << EOF
vim.fn['program_filetypes'] = function()
    root = require('root')()
    require('program').setup({
        filetypes = {
            cpp = {
                compiler = {
                    exe = 'g++',
                    args = {
                        root..'/2020/main.cpp',
                        root..'/2020/utils.cpp',
                        '-o '..root..'/2020/main.out',
                        '-std=c++20',
                        '-Wall',
                        '-pedantic'
                    }
                },
                execution = {
                    args = {
                        root..'/2020/main.out',
                    },
                    end_args = {
                        '%:p:t:r'
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
