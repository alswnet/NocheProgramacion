// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

float TiempoInicial = 0;
float TiempoFinal = 0;

void setup() {
  Serial.begin(115200);
  TiempoInicial = micros();
   String html = R"====(
<p> SALIDA #0  </p>
<p> SALIDA #1  </p>
<p> SALIDA #2  </p>
<p> SALIDA #3  </p>
<p> SALIDA #4  </p>
<p> SALIDA #5  </p>
<p> SALIDA #6  </p>
<p> SALIDA #7  </p>
<p> SALIDA #8  </p>
<p> SALIDA #9  </p>
<p> SALIDA #10  </p>
<p> SALIDA #11  </p>
<p> SALIDA #12  </p>
<p> SALIDA #13  </p>
<p> SALIDA #14  </p>
<p> SALIDA #15  </p>
<p> SALIDA #16  </p>
<p> SALIDA #17  </p>
<p> SALIDA #18  </p>
<p> SALIDA #19  </p>
<p> SALIDA #20  </p>
<p> SALIDA #21  </p>
<p> SALIDA #22  </p>
<p> SALIDA #23  </p>
<p> SALIDA #24  </p>
<p> SALIDA #25  </p>
<p> SALIDA #26  </p>
<p> SALIDA #27  </p>
<p> SALIDA #28  </p>
<p> SALIDA #29  </p>
<p> SALIDA #30  </p>
<p> SALIDA #31  </p>
<p> SALIDA #32  </p>
<p> SALIDA #33  </p>
<p> SALIDA #34  </p>
<p> SALIDA #35  </p>
<p> SALIDA #36  </p>
<p> SALIDA #37  </p>
<p> SALIDA #38  </p>
<p> SALIDA #39  </p>
<p> SALIDA #40  </p>
<p> SALIDA #41  </p>
<p> SALIDA #42  </p>
<p> SALIDA #43  </p>
<p> SALIDA #44  </p>
<p> SALIDA #45  </p>
<p> SALIDA #46  </p>
<p> SALIDA #47  </p>
<p> SALIDA #48  </p>
<p> SALIDA #49  </p>
<p> SALIDA #50  </p>
<p> SALIDA #51  </p>
<p> SALIDA #52  </p>
<p> SALIDA #53  </p>
<p> SALIDA #54  </p>
<p> SALIDA #55  </p>
<p> SALIDA #56  </p>
<p> SALIDA #57  </p>
<p> SALIDA #58  </p>
<p> SALIDA #59  </p>
<p> SALIDA #60  </p>
<p> SALIDA #61  </p>
<p> SALIDA #62  </p>
<p> SALIDA #63  </p>
<p> SALIDA #64  </p>
<p> SALIDA #65  </p>
<p> SALIDA #66  </p>
<p> SALIDA #67  </p>
<p> SALIDA #68  </p>
<p> SALIDA #69  </p>
<p> SALIDA #70  </p>
<p> SALIDA #71  </p>
<p> SALIDA #72  </p>
<p> SALIDA #73  </p>
<p> SALIDA #74  </p>
<p> SALIDA #75  </p>
<p> SALIDA #76  </p>
<p> SALIDA #77  </p>
<p> SALIDA #78  </p>
<p> SALIDA #79  </p>
<p> SALIDA #80  </p>
<p> SALIDA #81  </p>
<p> SALIDA #82  </p>
<p> SALIDA #83  </p>
<p> SALIDA #84  </p>
<p> SALIDA #85  </p>
<p> SALIDA #86  </p>
<p> SALIDA #87  </p>
<p> SALIDA #88  </p>
<p> SALIDA #89  </p>
<p> SALIDA #90  </p>
<p> SALIDA #91  </p>
<p> SALIDA #92  </p>
<p> SALIDA #93  </p>
<p> SALIDA #94  </p>
<p> SALIDA #95  </p>
<p> SALIDA #96  </p>
<p> SALIDA #97  </p>
<p> SALIDA #98  </p>
<p> SALIDA #99  </p>
)====";

  TiempoFinal = micros();
  while (!Serial) {}
//  Serial.println(html);
  Serial.print("El codigo tardo ");
  Serial.println(TiempoFinal - TiempoInicial);



}

void loop() {
}
