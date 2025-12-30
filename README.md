<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <title>Minishell</title>
</head>
<body>

<h1>Minishell</h1>

<p><strong>Projet réalisé dans le cadre du cursus de l’école 42.</strong></p>

<hr>

<h2>Description</h2>

<p>
Minishell est une implémentation simplifiée d’un shell Unix, inspirée de bash.
L’objectif du projet est de comprendre le fonctionnement interne d’un shell :
parsing des commandes, gestion des processus, redirections, pipes et signaux.
</p>

<hr>

<h2>Objectifs pédagogiques</h2>

<ul>
  <li>Comprendre le fonctionnement d’un shell Unix</li>
  <li>Manipuler les processus et les appels système</li>
  <li>Gérer les signaux</li>
  <li>Implémenter un parsing robuste</li>
  <li>Assurer une gestion correcte de la mémoire</li>
</ul>

<hr>

<h2>Fonctionnalités</h2>

<h3>Commandes</h3>
<ul>
  <li>Exécution de commandes via le PATH</li>
  <li>Gestion des chemins absolus et relatifs</li>
</ul>

<h3>Built-ins implémentés</h3>
<ul>
  <li>echo (option -n)</li>
  <li>cd</li>
  <li>pwd</li>
  <li>export</li>
  <li>unset</li>
  <li>env</li>
  <li>exit</li>
</ul>

<h3>Redirections</h3>
<ul>
  <li>&lt; redirection d’entrée</li>
  <li>&gt; redirection de sortie</li>
  <li>&gt;&gt; redirection en mode append</li>
  <li>&lt;&lt; heredoc</li>
</ul>

<h3>Pipes</h3>
<ul>
  <li>Gestion des pipes entre plusieurs commandes</li>
</ul>

<h3>Variables d’environnement</h3>
<ul>
  <li>Expansion des variables</li>
  <li>Gestion de la variable <code>$?</code></li>
</ul>

<h3>Signaux</h3>
<ul>
  <li>Gestion de SIGINT (Ctrl-C)</li>
  <li>Gestion de SIGQUIT (Ctrl-\)</li>
</ul>

<hr>

<h2>Contraintes du projet</h2>

<ul>
  <li>Langage : C</li>
  <li>Projet soumis à des fonctions autorisées limitées</li>
  <li>Gestion manuelle de la mémoire</li>
  <li>Respect de la norme de codage de l’école 42</li>
</ul>

<hr>

<h2>Compilation et exécution</h2>

<pre>
make
./minishell
</pre>

<hr>

<h2>Remarque</h2>

<p>
Ce projet a pour but pédagogique de reproduire le comportement d’un shell,
et non de remplacer bash.
</p>

</body>
</html>
