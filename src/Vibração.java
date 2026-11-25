import java.util.Scanner;

public class Vibração {
 public static void main(String[] args) {
Scanner scanner = new Scanner(System.in);

System.out.print("Digite a frequência da vibração (em Hz): ");
double frequency = scanner.nextDouble();

 System.out.print("Digite a velocidade (em m/s): "  );
double amplitude = scanner.nextDouble();

System.out.print("Digite o fator de conversão: "  );
double phase = scanner.nextDouble(); 
 
 System.out.print("A Frequência fundamental da vibração é: " + frequency + " Hz");
 scanner.close();
 }

}


// Explicação do cálculo: Ele calcula a frequência fundamental da vibração a partir da rotação de uma máquina com base na velocidade e fator de conversão e na frequência de vibração.

// Diferença entre os tipos de frequência: a Frequência fundamental é a mais baixa de uma máquina, enquanto a frequência de vibração usada para fazer o cálculo é qualquer frequência que a máquina pode gerar.



// Referências(Em C++): https://www.mathworks.com/help/signal/ug/generate-cpp-code-that-analyzes-vibration-signals-from-rotating-machinery.html