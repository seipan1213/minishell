# minishell(自作Shell)
## Moive
https://user-images.githubusercontent.com/38822155/171229427-d660ecb1-58c1-436a-964a-33b54a71287b.mp4
## Setup
```
git clone git@github.com:seipan1213/minishell.git && cd minishell
brew install readline
make
```
## MyBuiltin
- `echo `   
  - option
    - `n`
- `exit`
- `cd`
- `env`
- `export`
- `pwd`
- `unset`

## Special Char
- `<`
- `<<`
- `>`
- `>>`
- `|`
- `;`
- `'`
- `"`

## Other
- singal
- environ
- exit status
- PATH
- command history

## Test
- テストコマンドは`tests/input/`に定義
- bashのバージョンによってはエラーが出る。
```
cd tests
sh test.sh
```
