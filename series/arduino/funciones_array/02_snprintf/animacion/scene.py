from manim import *


class array_cuadros(Scene):
    def construct(self):
        cuadrados = VGroup()
        textos = VGroup()
        Texto = "Hola mundo"
        textoCodigo = Text("chat mensaje[10];", font="Comic Code Ligatures")

        for i in range(-5, 5):
            TextoTemporal = Text(Texto[i - 5], font="Comic Code Ligatures")
            cuadroActual = Square(side_length=0.8)
            cuadroActual.shift(i * RIGHT + 0.5 * RIGHT)
            TextoTemporal.shift(i * RIGHT + 0.5 * RIGHT)
            textos.add(TextoTemporal)
            cuadrados.add(cuadroActual)
        textoCodigo.next_to(cuadrados, UP * 2)

        self.play(Write(textoCodigo))

        self.play(Write(cuadrados, run_time=5))

        self.play(Write(textos, run_time=5))




class ejemplo_snprintf(Scene):
    def construct(self):
        Textos = [
            "snprintf(mensaje, 100,",
            '"Entero:',
            "%d",
            "Decimal:",
            "%f",
            '"',
            ",",
            "entero",
            ",",
            "decimal",
            ");",
        ]
        mensaje = VGroup()
        crearEntero = Text("int entero = 7;", font="Comic Code Ligatures").scale(0.45) 
        crearDecimal =  Text("float decimal = 12.12;", font="Comic Code Ligatures").scale(0.45)
        entero = Text("7", font="Comic Code Ligatures").scale(0.45)
        decimal = Text("12.12", font="Comic Code Ligatures").scale(0.45)
        for texto in Textos:
            textoTemporal = Text(texto, font="Comic Code Ligatures")
            mensaje.add(textoTemporal)
        mensaje.arrange(buff=0.5)
        mensaje.scale(0.49)
        # print(mensaje.height, mensaje.width)
        crearDecimal.next_to(mensaje, UP * 1.5)
        crearDecimal.align_to(mensaje, LEFT)
        crearEntero.next_to(crearDecimal, UP * 1.5)
        crearEntero.align_to(crearDecimal, LEFT)

        self.play(Write(mensaje), Write(crearEntero), Write(crearDecimal))
        self.play(mensaje[1:6].animate.shift(DOWN * 1.5))

        entero.set_x(mensaje[7].get_x())
        decimal.set_x(mensaje[9].get_x())
        self.play(Transform(mensaje[7], entero), Transform(mensaje[9], decimal))
        self.play(
            FadeOut(mensaje[2]),
            FadeOut(mensaje[4]),
            mensaje[7].animate.move_to(mensaje[2]),
            mensaje[9].animate.next_to(mensaje[3], RIGHT),
            mensaje[5].animate.next_to(mensaje[5], RIGHT * 1.5),
        )
        self.wait(2)
