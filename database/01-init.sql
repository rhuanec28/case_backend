-- Este arquivo é executado a cada vez que a nova imagem do postgres é criada

-- Dando permissões full ao usuário postgres
GRANT TEMP ON DATABASE LOJA_INTEGRADA TO postgres;
GRANT SELECT, INSERT, UPDATE, DELETE ON ALL TABLES IN SCHEMA public TO postgres;
GRANT EXECUTE ON ALL FUNCTIONS IN SCHEMA public TO postgres;
GRANT USAGE ON ALL SEQUENCES IN SCHEMA public TO postgres;

-- Tabela de itens, que possui os itens que podem ser adicionados ao carrinho
-- Para o ID gerado automaticamente utilizei a coluna de tipo Serial, por motivos de simplicidade
-- Para o preço dos itens foi utilizada um valor forçado com apenas 2 casas decimais por motivos de simplicidade, já que em transações mais precisas sei que o banco pode arredondar o valor de maneira incorreta.
CREATE TABLE ITEM (
   ID SERIAL PRIMARY KEY,
   CODE VARCHAR (50) NOT NULL,
   PRICE NUMERIC(5, 2) NOT NULL,
   STOCK INT NOT NULL
);

-- Tabela contendo os carrinhos para cada usuário
-- Utilizei uma coluna única chamada USER para simular um carrinho por sessão/usuário logado
CREATE TABLE CART (
   ID SERIAL PRIMARY KEY,
   USER_ID VARCHAR (50) UNIQUE NOT NULL
);

CREATE TABLE CART_ITEM (
   ITEM_ID INT,
   CART_ID INT,
   QUANTITY INT NOT NULL,
   PRIMARY KEY (ITEM_ID, CART_ID),
   FOREIGN KEY (ITEM_ID) REFERENCES ITEM (ID),
   FOREIGN KEY (CART_ID) REFERENCES CART (ID)
);

-- Itens fictícios para mock
-- Stock é a quantidade do item em estoque
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_1', 1.99, 50);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_2', 2.00, 0);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_3', 2.50, 10);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_4', 50.00, 20);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_5', 130.49, 1);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_6', 10.99, 234);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_7', 11.99, 123);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_8', 12.99, 999);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_9', 79.99, 12);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_10', 8.99, 42);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_11', 2.49, 250);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_12', 5.00, 150);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_13', 10.19, 25);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_14', 25.00, 1000);
INSERT INTO ITEM (CODE, PRICE, STOCK) VALUES ('ITEM_15', 199.99, 80);