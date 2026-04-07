all: page_renamer.exe page_split.exe parse_page.exe

page_split.exe: page_split.c file_utils.c
	gcc page_split.c file_utils.c -o page_split.exe

page_renamer.exe: page_renamer.c file_utils.c string_utils.c
	gcc page_renamer.c file_utils.c string_utils.c -o page_renamer.exe

parse_page.exe: parse_page.c
	gcc parse_page.c string_utils.c -o parse_page.exe

clean:
	rm -f page_renamer.exe
