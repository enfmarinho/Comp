# Como Rodar o Programa

1. Na pasta raiz do projeto, rode o comando:

   ```bash
   make
   ```

2. Após isso, o binario do programa será gerado no caminho build/comp, para executa-lo utilize:

   ```bash
   ./build/comp [caminho.c] < ../example/[nome_do_exemplo]
   ```

   > Substitua `[nome_do_exemplo]` pelo nome do arquivo de exemplo desejado.
   > Ademais, é possível explicitar o caminho do arquivo de saída do código de três enderecos substituindo `[caminho.c]` pelo caminho desejado, caso
não explicitado sera utilizado three_code_address.c

3. Então, para compilar o código de três enderecos, utilize:

   ```bash
   gcc three_code_address.c -lm
   ```

   > Note que caso `[caminho.c]` tenha sido definido na etapa anterior será necessario substituir three_code_address.c por `[caminho.c]`
   > Inclusive, a biblioteca da linguagem comp25 utiliza math.h e, para que o compilador localize essa biblioteca C é necessário a flag "-lm"
