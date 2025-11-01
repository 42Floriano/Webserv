<?php
// Vérifie si un fichier a été envoyé
if (isset($_FILES['file'])) {
    $uploadDir = __DIR__ . '/upload/'; // dossier de destination
    $uploadFile = $uploadDir . basename($_FILES['file']['name']);

    // Crée le dossier si nécessaire
    if (!is_dir($uploadDir)) {
        mkdir($uploadDir, 0777, true);
    }

    // Déplace le fichier depuis le dossier temporaire
    if (move_uploaded_file($_FILES['file']['tmp_name'], $uploadFile)) {
        echo "✅ Fichier envoyé avec succès : " . htmlspecialchars($_FILES['file']['name']);
    } else {
        echo "❌ Erreur lors du déplacement du fichier.";
    }
} else {
    echo "⚠️ Aucun fichier reçu ou erreur d’upload.";
}
?>