import argparse



if __name__ == "__main__":
	parser = argparse.ArgumentParser()

	# Agrego parametros
	parser.add_argument('-m', '--method', help='Es el metodo a ejecutar', default='1')
	parser.add_argument('-d', '--dataset', help='Archivo de entrada con datos de entrenamiento')
	parser.add_argument('-o', '--classif', help='Archivo de salida', default='out.txt')

	# Leo parametros.
	settings = parser.parse_args()

	print(settings.method)
	print(settings.dataset)
	print(settings.classif)


	#1
	import sentiment

	#2
	import pandas as pd

	import numpy as np

	#!cd ../data && tar -xvf *.tgz

	df_train = pd.read_csv("../data/imdb_small.csv", index_col=0)
	df = pd.read_csv(settings.dataset, index_col=0)

	#print("Cantidad de documentos: {}".format(df.shape[0]))


	#3
	#df.describe()

	#4
	text_train = df_train[df_train.type == 'train']["review"]
	label_train = df_train[df_train.type == 'train']["label"]

	text_test = df[df.type == 'test']["review"]
	label_test = df[df.type == 'test']["label"]

	#print("Cantidad de instancias de entrenamiento = {}".format(len(text_train)))
	#print("Cantidad de instancias de test = {}".format(len(text_test)))


	#5
	import time
	from sklearn.feature_extraction.text import CountVectorizer
	def run(max_alpha_, min_alpha_, alpha_step_, max_df_=0.90, min_df_=0.01, max_features_=5000, knn_neighbours_=100):
	    vectorizer = CountVectorizer(max_df=max_df_, min_df=min_df_, max_features=max_features_)
	    vectorizer.fit(text_train)

	    X_train, y_train = vectorizer.transform(text_train), (label_train == 'pos').values
	    X_test, y_test = vectorizer.transform(text_test), (label_test == 'pos').values

	    #import sentiment
	    print("hola")
	    clf = sentiment.KNNClassifier(knn_neighbours_)
	    pca = sentiment.PCA(max_alpha_)
	    #fitteo con el x_train calculado arriba
	    pca.fit(X_train,10000, 0.0000000001)
	    
	    #loopeo para todos los alphas
	    for alpha_ in range(min_alpha_, max_alpha_, alpha_step_):
	        pca_X_train = pca.transform(X_train, alpha_)
	        pca_X_test = pca.transform(X_test,alpha_)

	        #Timing starts, same as previous cell:
	        start = time.time()

	        clf.fit(pca_X_train, y_train)
	        from sklearn.metrics import accuracy_score
	        from sklearn.metrics import precision_score
	        from sklearn.metrics import recall_score

	        y_pred = clf.predict(pca_X_test)
	        print(y_pred)
	        acc = accuracy_score(y_test, y_pred)
	        pre = precision_score(y_test, y_pred)
	        rec = recall_score(y_test, y_pred)
	        f1 = 2*(pre*rec)/(pre+rec)
	        #Timing ends, again, like in previous cell.
	        end = time.time()
	        delta_time = end - start
	        delta_time_str = str(round(delta_time, 2))
	        f = open(settings.classif, "+a")
	        f.write("\n")
	        for i in range(len(y_pred)):
	        	if y_pred[i] == 0:
	        		f.write("neg\n")
	        	else:
	        		f.write("pos\n")
	    return acc
		#return file to write


	import time
	from sklearn.feature_extraction.text import CountVectorizer
	def run_knn_no_pca(max_df_=0.90, min_df_=0.01, max_features_=5000, knn_neighbours_=100, alpha_=30):
		vectorizer = CountVectorizer(max_df=max_df_, min_df=min_df_, max_features=max_features_)
		vectorizer.fit(text_train)

		X_train, y_train = vectorizer.transform(text_train), (label_train == 'pos').values
		X_test, y_test = vectorizer.transform(text_test), (label_test == 'pos').values

		import sentiment
		clf = sentiment.KNNClassifier(knn_neighbours_)



		clf.fit(X_train, y_train)
		#clf.fit(pca_X_train, y_train)
		from sklearn.metrics import accuracy_score
		from sklearn.metrics import precision_score
		from sklearn.metrics import recall_score

		y_pred = clf.predict(X_test)
		#y_pred = clf.predict(pca_X_test)
       	f = open(settings.classif, "+a")
       	f.write("\n")
	        for i in range(len(y_pred)):
	        	if y_pred[i] == 0:
	        		f.write("neg\n")
	        	else:
	        		f.write("pos\n")
		return acc

max_df_ = 0.3725
min_df_ =  0.01
max_features_ = 5000
knn_neighbours_ = 110
alpha_ = 300

data = settings.dataset
res_file = settings.classif

if settings.method == "1":
	print("metodo con pca")
	print(run(alpha_+1, alpha_, 1, max_df_, min_df_, max_features_, knn_neighbours_))
else:
	print("metodo sin pca")
	print(run_knn_no_pca(max_df_, min_df_, max_features_, knn_neighbours_))