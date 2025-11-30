import io
import csv

import streamlit as st
import pandas as pd


class GeneradorNumerosPseudoaleatorios:
    def __init__(self, semilla, cifras):
        self.semilla = semilla
        self.cifras = cifras
        self.tabla = []

    def procedimiento_cuadrado_medio(self):
        self.tabla = []
        rn = self.semilla
        iteraciones = 0
        MAX_ITERACIONES = 10000

        # conjunto para detectar repetidos en la secuencia de R(n)
        vistos = set()

        # mientras rn no sea 0, no excedamos max iteraciones y no se repita
        while rn != 0 and iteraciones < MAX_ITERACIONES and rn not in vistos:
            # marcamos este rn como ya visto
            vistos.add(rn)

            rn2 = rn * rn
            s = str(rn2)

            # Ajuste de longitud para que la extracción del centro sea consistente
            if (len(s) % 2 == 0 and self.cifras % 2 != 0) or \
               (len(s) % 2 != 0 and self.cifras % 2 == 0):
                s = "0" + s

            centro = s
            while len(centro) > self.cifras:
                centro = centro[1:-1]

            centro_int = int(centro) if centro else 0

            registro = {
                'n': iteraciones,
                'Rn': rn,
                'Rn2': rn2,
                'medio': centro_int
            }

            self.tabla.append(registro)
            rn = centro_int
            iteraciones += 1

        return self.tabla

    def numeros_pseudoaleatorios(self):
        self.procedimiento_cuadrado_medio()
        return [r['medio'] for r in self.tabla]


def generar_csv(tabla, cifras: int) -> bytes:
    """Genera el CSV en memoria a partir de la tabla."""
    modulus = 10 ** cifras
    output = io.StringIO()
    writer = csv.writer(output)

    writer.writerow(['R(n)', 'R(n)^2', 'M.R(n)^2', 'u'])

    for r in tabla:
        u = r['medio'] / modulus
        writer.writerow(
            [r['Rn'], r['Rn2'], r['medio'], f"{u:.6f}"]
        )

    return output.getvalue().encode("utf-8")


def main():
    st.title("Generador de números pseudoaleatorios")
    st.subheader("Método del cuadrado medio")

    st.markdown(
        """
        Ingresa una **semilla entera** y el **número de cifras** que se usarán
        para generar la secuencia de números pseudoaleatorios mediante el método
        del cuadrado medio.
        """
    )

    # Entradas del usuario
    semilla = st.number_input(
        "Semilla inicial (entero)",
        min_value=0,
        value=1234,
        step=1,
        format="%d"
    )

    cifras = st.number_input(
        "Número de cifras",
        min_value=1,
        value=4,
        step=1,
        format="%d"
    )

    if st.button("Generar secuencia"):
        generador = GeneradorNumerosPseudoaleatorios(int(semilla), int(cifras))
        tabla = generador.procedimiento_cuadrado_medio()

        if len(tabla) >= 10000:
            st.warning(
                "La secuencia alcanzó el límite máximo de 10,000 iteraciones "
                "y puede haber sido truncada para evitar un ciclo infinito."
            )

        modulus = 10 ** int(cifras)

        # Convertir la tabla a DataFrame para mostrarla
        df = pd.DataFrame(
            [
                {
                    "n": r["n"],
                    "R(n)": r["Rn"],
                    "R(n)^2": r["Rn2"],
                    "M.R(n)^2": r["medio"],
                    "u": r["medio"] / modulus
                }
                for r in tabla
            ]
        )

        st.subheader("Tabla generada")
        st.dataframe(df, use_container_width=True)

        # Botón para descargar el CSV
        csv_bytes = generar_csv(tabla, int(cifras))
        st.download_button(
            label="📥 Descargar CSV",
            data=csv_bytes,
            file_name="cuadrado_medio.csv",
            mime="text/csv"
        )


if __name__ == "__main__":
    main()
