#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <type_traits>
#include <algorithm>
#include <limits>
#include <iterator>
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    inline constexpr std::size_t ascii_max_blocks_limit = 200;

    inline void print_positive_bar(std::size_t blocks, const std::string& block_char);
    inline void print_negative_bar(std::size_t blocks, const std::string& block_char);
    inline void print_single_bar(std::size_t blocks, const std::string& block_char, bool is_negative);

    inline std::size_t safe_block_count(double value, std::size_t limit)
    {
        const std::size_t bounded_limit = std::min(limit, ascii_max_blocks_limit);
        if (!std::isfinite(value) || value <= 0.0 || bounded_limit == 0) return 0;
        if (value >= static_cast<double>(bounded_limit)) return bounded_limit;

        const long rounded = std::lround(value);
        if (rounded <= 0) return 0;
        return std::min(static_cast<std::size_t>(rounded), bounded_limit);
    }

    // ============================================================
    // CONFIGURACIÓN DEL GRÁFICO
    // ============================================================
    
    struct AsciiChartConfig
    {
        std::size_t max_blocks = 30;           // Bloques máximos para el valor más alto
        std::string block_char = "█";          // Carácter para la barra
        bool show_values = true;               // Mostrar valores numéricos
        bool normalize = true;                 // Normalizar contra el máximo
        double min_value = std::numeric_limits<double>::quiet_NaN();
        double max_value = std::numeric_limits<double>::quiet_NaN();
        std::string label_prefix = "";         // Prefijo para etiquetas
        std::string label_suffix = "";         // Sufijo para etiquetas
    };
    
    // ============================================================
    // TRAITS PARA DETECTAR TIPOS NUMÉRICOS
    // ============================================================
    
    template <typename T>
    struct is_numeric_container : std::false_type {};
    
    template <typename T>
    struct is_numeric_container<std::vector<T>> : std::is_arithmetic<T> {};
    
    template <typename T>
    struct is_numeric_container<std::list<T>> : std::is_arithmetic<T> {};
    
    template <typename T>
    struct is_numeric_container<std::deque<T>> : std::is_arithmetic<T> {};
    
    template <typename T, std::size_t N>
    struct is_numeric_container<std::array<T, N>> : std::is_arithmetic<T> {};
    
    template <typename T>
    inline constexpr bool is_numeric_container_v = is_numeric_container<std::decay_t<T>>::value;
    
    // ============================================================
    // FUNCIÓN PRINCIPAL CON CONFIGURACIÓN
    // ============================================================
    
    template <typename Container>
    void cout_ascii(const std::string& name, const Container& container,
                    const AsciiChartConfig& config)
    {
        static_assert(is_numeric_container_v<Container>,
                      "cout_ascii solo soporta contenedores de tipos numéricos");
        
        // Verificar contenedor vacío
        if (std::empty(container)) {
            detail::print_name(std::cout, name);
            std::cout << " [contenedor vacío]\n";
            return;
        }
        
        // Encontrar min y max (sin usar std::minmax_element para manejar todos los casos)
        auto it = std::begin(container);
        auto end = std::end(container);
        
        using ElementType = typename std::iterator_traits<decltype(it)>::value_type;
        
        ElementType min_val = *it;
        ElementType max_val = *it;
        bool has_negative = false;
        
        for (; it != end; ++it) {
            const auto& val = *it;
            if (val < min_val) min_val = val;
            if (val > max_val) max_val = val;
            if (val < 0) has_negative = true;
        }
        
        // Mostrar título
        detail::print_name(std::cout, name);
        std::cout << ":\n";
        
        // Mostrar información de escala
        detail::print_syntax(std::cout, "  (");
        std::cout << "min=" << detail::color::number << min_val << detail::color::reset;
        detail::print_syntax(std::cout, ", max=");
        std::cout << detail::color::number << max_val << detail::color::reset;
        detail::print_syntax(std::cout, ")\n");
        
        // Configuración adaptativa
        AsciiChartConfig cfg = config;
        if (cfg.max_blocks == 0) cfg.max_blocks = 30;
        cfg.max_blocks = std::min(cfg.max_blocks, ascii_max_blocks_limit);
        
        // Para números negativos, necesitamos dos barras (negativa y positiva)
        const bool use_dual_bars = has_negative && cfg.normalize;
        const double scale_min = std::isnan(cfg.min_value) ? static_cast<double>(min_val) : cfg.min_value;
        const double scale_max = std::isnan(cfg.max_value) ? static_cast<double>(max_val) : cfg.max_value;
        const double max_abs = std::max(std::abs(scale_max), std::abs(scale_min));
        
        // Dibujar el gráfico
        for (const auto& num : container) {
            // Etiqueta con formato
            std::string label = cfg.label_prefix + std::to_string(num) + cfg.label_suffix;
            
            if (cfg.show_values) {
                std::cout << label << " ";
            }
            
            // Calcular longitud de la barra
            std::size_t blocks = 0;
            bool is_negative = num < 0;
            
            if (cfg.normalize) {
                // Normalización contra el máximo absoluto
                if (max_abs > 0) {
                    double normalized = std::abs(static_cast<double>(num)) / max_abs;
                    blocks = safe_block_count(normalized * static_cast<double>(cfg.max_blocks), cfg.max_blocks);
                }
                
                // Para números negativos con dual bars, usar un separador
                if (use_dual_bars && is_negative) {
                    // Primero mostrar barra negativa
                    print_negative_bar(blocks, cfg.block_char);
                    std::cout << "|";
                    // No mostrar barra positiva para negativos
                } else if (use_dual_bars && !is_negative) {
                    // Para positivos, mostrar barra positiva
                    std::cout << "|";
                    print_positive_bar(blocks, cfg.block_char);
                } else {
                    // Barra simple (todos los números en misma dirección)
                    print_single_bar(blocks, cfg.block_char, is_negative);
                }
            } else {
                // Sin normalización (usar escala absoluta)
                double abs_num = std::abs(static_cast<double>(num));
                blocks = safe_block_count(abs_num, cfg.max_blocks);
                
                if (blocks > 0) {
                    if (is_negative) {
                        print_negative_bar(blocks, cfg.block_char);
                    } else {
                        print_positive_bar(blocks, cfg.block_char);
                    }
                } else if (num == 0) {
                    std::cout << " ";
                }
            }
            
            std::cout << "\n";
        }
    }
    
    // ============================================================
    // FUNCIONES DE AYUDA PARA DIBUJAR BARRAS
    // ============================================================
    
    inline void print_positive_bar(std::size_t blocks, const std::string& block_char)
    {
        std::cout << detail::color::success;
        for (std::size_t i = 0; i < blocks; ++i) std::cout << block_char;
        std::cout << detail::color::reset;
    }

    inline void print_negative_bar(std::size_t blocks, const std::string& block_char)
    {
        std::cout << detail::color::error;
        for (std::size_t i = 0; i < blocks; ++i) std::cout << block_char;
        std::cout << detail::color::reset;
    }
    
    inline void print_single_bar(std::size_t blocks, const std::string& block_char, bool is_negative)
    {
        if (is_negative) {
            print_negative_bar(blocks, block_char);
        } else {
            print_positive_bar(blocks, block_char);
        }
    }
    
    // ============================================================
    // SOBRECARGAS CONVENIENTES
    // ============================================================
    
    template <typename Container>
    void cout_ascii(const std::string& name, const Container& container) {
        cout_ascii(name, container, AsciiChartConfig{});
    }
    
    template <typename Container>
    void cout_ascii(const Container& container) {
        cout_ascii("ASCII Chart", container);
    }
    
    // Sobrecarga específica para vector<int> (compatibilidad hacia atrás)
    inline void cout_ascii(const std::string& name, const std::vector<int>& nums,
                          std::size_t max_blocks = 30) {
        AsciiChartConfig config;
        config.max_blocks = max_blocks;
        cout_ascii(name, nums, config);
    }
    
    inline void cout_ascii(const std::vector<int>& nums, std::size_t max_blocks = 30) {
        cout_ascii("ASCII Chart", nums, max_blocks);
    }
    
    // ============================================================
    // FUNCIONES ESPECIALES PARA DIFERENTES ESCENARIOS
    // ============================================================
    
    // Gráfico de barras horizontales (mejor para comparar)
    template <typename Container>
    void cout_hbar(const std::string& name, const Container& container,
                   std::size_t max_width = 40) {
        AsciiChartConfig config;
        config.max_blocks = max_width;
        config.show_values = true;
        cout_ascii(name, container, config);
    }
    
    // Gráfico de barras apiladas (para valores positivos y negativos)
    template <typename Container>
    void cout_stacked_bar(const std::string& name, const Container& container,
                          std::size_t max_width = 40) {
        AsciiChartConfig config;
        config.max_blocks = max_width;
        config.show_values = false; // Los valores se muestran en las barras
        cout_ascii(name, container, config);
    }
    
    // Gráfico con escala personalizada
    template <typename Container>
    void cout_custom_ascii(const std::string& name, const Container& container,
                          double min_value, double max_value, std::size_t max_blocks = 30) {
        AsciiChartConfig config;
        config.max_blocks = max_blocks;
        config.min_value = min_value;
        config.max_value = max_value;
        cout_ascii(name, container, config);
    }
}
