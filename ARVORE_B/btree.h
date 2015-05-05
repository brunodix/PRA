#ifndef BTREE_H
#define BTREE_H

http://www.geeksforgeeks.org/b-tree-set-1-insert-2/

const int T = 2,
	MAX_KEYS = 2 * T - 1,
	MAX_CHILDREN = 2 * T - 1,
	MIN_ELEMENTS = T - 1;


class Node {
	private:
		Node *children[MAX_CHILDREN];
		Node *keys[MAX_CHILDREN];
		int keyCount;
	public:

};

class BTree {
	private:
		Node *root;

		long binarySearch(int key) {
			return 0;
		}
	public:
		void insertKey(int key, Node *node) {
			int k, pos;
			// obtem o endereco para insercao da nova chave
			pos = binarySearch(key);
			k = root->keyCount;
			// libera espaco para insercao da chave na pagina
			while( k > pos && info < root->keys[k−1]){
				root->keys[k] = root->keys[k−1];
				root->children[k+1] = root->children[k];
				k−−;
			}
			// insere a chave
			root −>keys[pos] = key;
			root −>filhos[k+1] = node;
			root −>keys++;
		};
		void insert() {
			
		}

		arvoreB∗ insere(int info, bool ∗h, int ∗info retorno) {
			int i , j , pos, info mediano;
			arvoreB ∗temp, ∗filho dir ;
			if ( ! root ) {
				*h = true; // atingiu no folha
				∗info retorno = info;
				return NULL;
			} else {
				pos = busca binaria ( root , info );
				if ( root−>keyCount > pos && root−>keys[ pos ] == info ) {
					printf ( "Chave ja contida na arvore " );
					∗h = false;
				} else {
					filho dir = insere( root−>filhos[ pos ], info , h, info retorno );
					if (∗h) {
						if (root−>keyCount < MAX_KEYS ) { // tem espaco na pagina
							insere chave (root , ∗info retorno, filho dir);
							∗h = false;
						} else { // overflow ! SPLIT−AND−PROMOTE
							temp = (arvoreB∗) malloc(sizeof(arvoreB));
							temp−>keyCount = 0;
							for (i = 0; i < MAX FILHOS; i++)
								temp−>filhos[ i ] = NULL;
					
							info mediano = root−>keys[ MIN_ELEMENTS ]; // PROMOTE

							// insere metade da pagina no temp (SPLIT)
							temp−>filhos[ 0 ] = root−>filhos[MIN_ELEMENTS+1];
							for (i=MIN_ELEMENTS+1; i<MAX_KEYS; i++)
								insere chaves ( temp, root−>keys[ i ], root−>filhos[ i + 1 ] );
							// atualiza raiz
							for (i = MIN_ELEMENTS; i < MAX_KEYS; i++) {
								root−>keys[ i ] = 0;
								root−>filhos[ i + 1 ] = NULL;
							}
							root−>keyCount = MIN_ELEMENTS;

							// verifica onde inserir a nova chave
							if (pos <= MIN_ELEMENTS)
								insere chave ( root , ∗info retorno , filho dir );
							else
								insere chave ( temp, ∗info retorno , filho dir );
							∗info retorno = info mediano;
							return temp;
						}
					}
				}
			}
}

};

#endif //BTREE_H
