# Registro de cambios

Este archivo registra cambios publicados y relevantes para usuarios y personas
que mantienen `cpp_printer`.

## v1.0.4

Fecha de publicación: pendiente de etiquetar.

- Se centralizaron los traits de contenedores en
  `cpp_printer/detail/type_traits.hpp`, eliminando definiciones duplicadas.
- `compare.hpp` y `diff.hpp` pueden incluirse juntos sin errores de
  redefinición; `all.hpp` ahora expone también `cout_diff`.
- Se redujeron copias y recorridos redundantes en comparación, diff, árbol,
  estadísticas, tabla y gráficos ASCII.
- Los gráficos ASCII calculan la escala una sola vez, reducen escrituras ANSI y
  `cout_custom_ascii` aplica los límites configurados.
- Las utilidades internas de recorrido reciben `std::ostream&`, facilitando
  reutilización y pruebas futuras.
- Se añadieron tests de herramientas y vistas, junto con ejemplos ejecutables
  para esos módulos.
- Se añadió integración continua para GCC y Clang en Linux, y MSVC en Windows;
  en cada push y pull request compila, ejecuta tests y valida los ejemplos.
- La documentación ahora incluye guía de arquitectura, reglas de mantenimiento
  y comandos de validación.

## v1.0.3

- Versión publicada anterior a v1.0.4.
