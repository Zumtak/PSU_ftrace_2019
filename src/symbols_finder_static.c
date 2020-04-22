/*
** EPITECH PROJECT, 2019
** Ftrace
** File description:
** Search for static symbols
*/

#include <elf.h>
#include <gelf.h>
#include <libelf.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char *get_symbol_name(unsigned long addr, Elf *elf, Elf_Scn *scn,
GElf_Shdr *shdr)
{
    Elf_Data *data = elf_getdata(scn, NULL);
    GElf_Sym sym;
    size_t nbr = shdr->sh_size / shdr->sh_entsize;
    size_t i = 0;

    for (i = 0; i < nbr; i = i + 1) {
        gelf_getsym(data, i, &(sym));
        if (sym.st_value == 0 || !(sym.st_name))
            continue;
        if (sym.st_value == (unsigned long)addr)
            return (elf_strptr(elf, shdr->sh_link, sym.st_name));
    }
    return (NULL);
}

static char *search(Elf *elf, unsigned long addr)
{
    Elf_Scn *scn = elf_nextscn(elf, NULL);
    GElf_Shdr shdr;
    char *func_name = NULL;

    while (scn != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr) {
            fprintf(stderr, "Problem :/\n");
            return (NULL);
        }
        if (shdr.sh_type != SHT_SYMTAB) {
            scn = elf_nextscn(elf, scn);
            continue;
        }
        func_name = get_symbol_name(addr, elf, scn, &(shdr));
        if (func_name)
            break;
        scn = elf_nextscn(elf, scn);
    }
    return (func_name);
}

static Elf *setup_elf(int fd)
{
    Elf *elf = NULL;

    if (elf_version(EV_CURRENT) == EV_NONE) {
        return (NULL);
    }
    elf = elf_begin(fd, ELF_C_READ, NULL);
    if (!(elf)) {
        return (NULL);
    }
    if (elf_kind(elf) != ELF_K_ELF) {
        return (NULL);
    }
    return (elf);
}

static int setup_file(char *file)
{
    int fd = open(file, O_RDONLY, 0);

    if (fd == -1) {
        perror(NULL);
        return (84);
    }
    return (fd);
}

char *find_symbol(char *file, unsigned long long int addr)
{
    int fd = setup_file(file);
    Elf *elf = NULL;
    char *func_name = NULL;

    if (fd != 84)
        elf = setup_elf(fd);
    else
        return (NULL);
    if (elf == NULL)
        return (NULL);
    func_name = search(elf, addr);
    if (func_name != NULL)
        func_name = strdup(func_name);
    elf_end(elf);
    close(fd);
    return (func_name);
}
