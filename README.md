# Lista de Compras

## O que é?
Este é um programa em C que cria uma lista de compras em csv, ele funciona pelo Terminal e ao finalizar o programa ele cria ou edita um arquivo csv já criado.  

## Como funciona?
Ao entrar no programa você deve digitar o nome da lista que deseja criar ou editar, por exemplo, eu quero criar a lista chamada 'Abril', caso eu queira adicionar mais itens ou alterar aquela lista eu devo digitar 'Abril' 
novamente.    
Dentro da lista você pode adicionar o nome do item (Que deve ser digitado igual se posteriormente você desejar adicionar mais itens, é caseSensitive) a quantidade daquele item, e o valor de cada unidade, após isso ele
vai conservar em uma posição, que só vai salvar no arquivo ao finalizar o programa.    
Para a atualização de uma lista, o código cria um arquivo temporario e o atual ele utiliza para obter os dados e colar nesse novo arquivo. "O por que disso?" simples, o total estava ficando repartido, a cada alteração uma
linha era consumida pelo total, ao fazer dessa forma o total vai sempre ficar apenas ao final do arquivo e não irá se repetir.
