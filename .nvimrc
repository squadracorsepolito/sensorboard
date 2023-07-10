set path+=**
nnoremap <F4> :!ptags --include-untracked --include-submodule<enter>
nnoremap <F5> :make -f Makefile_my -j build <bar> cwindow <enter>
nnoremap <F6> :!make -f Makefile_my flash<enter>
nnoremap <M-C-F> :w<enter>:!clang-format -style=file -i %<enter>