Projekt 2 — tłumacz C -> powłoka (zadanie nr 4)

Użycie:

1. Uruchom tłumacz, podając plik C jako argument:

```bash
bash translator.sh samples/example.c > out.sh
chmod +x out.sh
printf "3\n" | bash out.sh
```

2. Skrypt obsługuje prosty podzbiór C: deklaracje `int`, przypisania, `printf` z prostymi formatami,
   `scanf` z `%d`, `if/else`, `while` oraz proste `for` (przekonwertowane na `while`).

3. Diagnostyka: skrypt wypisze na stderr komunikaty `"[diagnostic] ..."` dla nieobsługiwanych
   wyrażeń (np. złożone warunki, wskaźniki, struktury itp.).

Ograniczenia:
- Nie obsługuje wskaźników, tablic, struktur, funkcji poza `main`, złożonych wyrażeń w `printf`/`scanf`.
- Tłumaczenie jest heurystyczne i działa tylko dla prostych, dobrze sformatowanych programów C.
