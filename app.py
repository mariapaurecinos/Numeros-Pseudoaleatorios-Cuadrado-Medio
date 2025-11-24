from flask import Flask, render_template, request, send_file
import io
import csv

app = Flask(__name__)


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


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/generar', methods=['POST'])
def generar():
    try:
        semilla = int(request.form['semilla'])
        cifras = int(request.form['cifras'])

        if cifras <= 0:
            return "Error: El número de cifras debe ser mayor a 0", 400

        generador = GeneradorNumerosPseudoaleatorios(semilla, cifras)
        tabla = generador.procedimiento_cuadrado_medio()

        if len(tabla) >= 10000:
            return "Advertencia: La secuencia alcanzó el límite máximo de 10,000 iteraciones y fue truncada para evitar un ciclo infinito.", 400

        output = io.StringIO()
        writer = csv.writer(output)

        modulus = 10**cifras
        writer.writerow(['n', 'R(n)', 'R(n)^2', 'M.R(n)^2', 'u'])

        for r in tabla:
            u = r['medio'] / modulus
            writer.writerow(
                [r['n'], r['Rn'], r['Rn2'], r['medio'], f"{u:.6f}"])

        output.seek(0)
        return send_file(io.BytesIO(output.getvalue().encode()),
                         mimetype='text/csv',
                         as_attachment=True,
                         download_name='cuadrado_medio.csv')

    except ValueError:
        return "Error: Por favor ingresa valores numéricos válidos", 400
    except Exception as e:
        return f"Error: {str(e)}", 500


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=False)
